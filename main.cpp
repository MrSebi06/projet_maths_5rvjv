#include <chrono>
#include <random>

#include "init.h"

#include "imgui-1.92.5/imgui.h"
#include "imgui-1.92.5/backends/imgui_impl_glfw.h"
#include "imgui-1.92.5/backends/imgui_impl_opengl3.h"
#include "Engine.h"
#include "GameObject.h"
#include "Mesh/Polygon/Square.h"
#include "Particles/Emitters/LiquidStreamEmitter.h"
#include "Particles/Emitters/SparkleEmitter.h"
#include "Physics/Shape.h"

#define WIDTH 800
#define HEIGHT 600
#define ASPECT_RATIO (static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))


enum class EmitterType {
    Sparkle,
    LiquidStream
};

enum class SpawnObjectType {
    Particles,

    StaticSphere,
    DynamicSphere,

    StaticSquare,
    DynamicSquare,
};

auto current_emitter_type = EmitterType::Sparkle;
auto current_spawn_object_type = SpawnObjectType::Particles;

void process_continuous_input(GLFWwindow *window, float dt);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);
Vector2 screen_to_world(float mouseX, float mouseY);
void window_size_callback(GLFWwindow *window, int width, int height);
void draw_ui();

struct Shaders {
    GLuint particle_shader_program;
    GLuint base_shader_program;
};

int main() {
    std::srand(std::time({}));

    GLFW_config();
    GLFWwindow *window = create_window(WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    GLAD_init();

    GLuint particle_shader_program = create_shader_program("particle.vert", "particle.frag");
    GLuint base_shader_program = create_shader_program("base.vert", "base.frag");

    Shaders shaders = {particle_shader_program, base_shader_program};

    glfwSetWindowUserPointer(window, &shaders);
    set_aspect_ratio(WIDTH, HEIGHT, particle_shader_program);
    set_aspect_ratio(WIDTH, HEIGHT, base_shader_program);

    Engine::init(particle_shader_program);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    float deltaTimes[200];
    int deltaIndex = 0;

    std::chrono::time_point<std::chrono::high_resolution_clock> last_tick = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time using system clock
        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto elapsed = current_time - last_tick;
        const auto elapsed_ms = duration_cast<std::chrono::microseconds>(elapsed);
        const float dt = elapsed_ms.count() / 1000000.0f;
        last_tick = current_time;

        process_continuous_input(window, dt);

        float averageDT = 0;
        for (float deltaTime: deltaTimes)
            averageDT += deltaTime;

        averageDT /= 200;

        if (dt < averageDT * 3)
            Engine::update(dt);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Engine::draw();

        glfwPollEvents();
        draw_ui();
        glfwSwapBuffers(window);

        deltaTimes[deltaIndex] = dt;
        deltaIndex = (deltaIndex + 1) % 200;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteProgram(particle_shader_program);

    glfwTerminate();

    return 0;
}


void process_continuous_input(GLFWwindow *window, const float dt) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    const Vector2 pos = screen_to_world(static_cast<float>(xpos), static_cast<float>(ypos));

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
        if (current_spawn_object_type == SpawnObjectType::Particles) {
            ParticleEmitter *emitter = nullptr;
            switch (current_emitter_type) {
                case EmitterType::Sparkle:
                    emitter = new SparkleEmitter(pos);
                    break;
                case EmitterType::LiquidStream:
                    emitter = new LiquidStreamEmitter(pos);
                    break;
            }
            emitter->play_for(dt + static_cast<float>(0.1), true);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(-0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(0, 0.1f));
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(0, -0.1f));
}


void mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    const Shaders shaders = *static_cast<Shaders *>(glfwGetWindowUserPointer(window));

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        const Vector2 pos = screen_to_world(static_cast<float>(xpos), static_cast<float>(ypos));

        switch (current_spawn_object_type) {
            case SpawnObjectType::StaticSphere: {
                const auto mesh = std::make_shared<Circle>(0.1f, 30);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                Engine::physics.registerRigidBody(game_object, 0.0, 0.5f, 0.5, new CircleShape(0.1f));
            }
            break;
            case SpawnObjectType::DynamicSphere: {
                const auto mesh = std::make_shared<Circle>(0.1f, 30);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                Engine::physics.registerRigidBody(game_object, 1.0, 0.5f, 0.5, new CircleShape(0.1f));
            }
            break;
            case SpawnObjectType::StaticSquare: {
                const auto mesh = std::make_shared<Square>(0.1f);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                Engine::physics.registerRigidBody(game_object, 0.0, 0.1f, 0.5, new BoxShape(0.2f, 0.2f));
            }
            break;
            case SpawnObjectType::DynamicSquare: {
                const auto mesh = std::make_shared<Square>(0.1f);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                Engine::physics.registerRigidBody(game_object, 1.0, 0.1f, 0.5, new BoxShape(0.2f, 0.2f));
            }
            break;
            default:
                break;
        }
    }
}

void key_callback(GLFWwindow *window, const int key, int scancode, int action, int mods) {
    // const Shaders shaders = *static_cast<Shaders *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Vector2 screen_to_world(const float mouseX, const float mouseY) {
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    const float x = (2.0f * mouseX / static_cast<float>(width) - 1.0f) * aspect;
    const float y = 1.0f - 2.0f * mouseY / static_cast<float>(height);
    return {x, y};
}

void window_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
    const Shaders shaders = *static_cast<Shaders *>(glfwGetWindowUserPointer(window));
    set_aspect_ratio(width, height, shaders.particle_shader_program);
    set_aspect_ratio(width, height, shaders.base_shader_program);
}

void draw_ui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static int particle_selected_idx = 0;
    static int spawn_object_selected_idx = 0;

    if (ImGui::BeginListBox("EmitterType")) {
        const char *particles[] = {"Sparkle", "LiquidStream"};
        for (int n = 0; n < IM_ARRAYSIZE(particles); n++) {
            const bool is_selected = (particle_selected_idx == n);
            if (ImGui::Selectable(particles[n], is_selected))
                particle_selected_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
                current_emitter_type = static_cast<EmitterType>(n);
            }
        }
        ImGui::EndListBox();
    }

    if (ImGui::BeginListBox("SpawnObjectType")) {
        const char *spawn_objects[] = {"Particles", "StaticSphere", "DynamicSphere", "StaticSquare", "DynamicSquare",};
        for (int n = 0; n < IM_ARRAYSIZE(spawn_objects); n++) {
            const bool is_selected = (spawn_object_selected_idx == n);
            if (ImGui::Selectable(spawn_objects[n], is_selected))
                spawn_object_selected_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected) {
                ImGui::SetItemDefaultFocus();
                current_spawn_object_type = static_cast<SpawnObjectType>(n);
            }
        }
        ImGui::EndListBox();
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
