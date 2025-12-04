#include <chrono>
#include <random>

#include "init.h"
#include "input.h"

#include "imgui-1.92.5/backends/imgui_impl_glfw.h"
#include "imgui-1.92.5/backends/imgui_impl_opengl3.h"
#include "Engine.h"
#include "Mesh/Polygon/Square.h"
#include "Particles/Emitters/LiquidStreamEmitter.h"
#include "Particles/Emitters/SparkleEmitter.h"
#include "Physics/CollisionShape.h"

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

void draw_ui();

int main() {
    std::srand(std::time({}));

    GLFWwindow *window = GLFW_init(800, 600);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);

    GLAD_init();
    IMGUI_init(window);

    const GLuint particle_shader_program = create_shader_program("particle.vert", "particle.frag");
    const GLuint base_shader_program = create_shader_program("base.vert", "base.frag");

    Shaders shaders = {particle_shader_program, base_shader_program};
    glfwSetWindowUserPointer(window, &shaders);
    set_aspect_ratio(800, 600, particle_shader_program);
    set_aspect_ratio(800, 600, base_shader_program);

    Engine::init(particle_shader_program, base_shader_program);

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
        for (const float deltaTime: deltaTimes)
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


void mouse_callback(GLFWwindow *window, const int button, const int action, int mods) {
    const Shaders shaders = *static_cast<Shaders *>(glfwGetWindowUserPointer(window));

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        const Vector2 pos = screen_to_world(static_cast<float>(xpos), static_cast<float>(ypos));

        switch (current_spawn_object_type) {
            case SpawnObjectType::StaticSphere: {
                const auto mesh = std::make_shared<CircleMesh>(0.1f, 30);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(0.0, 0.5f, 0.2, new CircleCollisionShape(0.1f), true);
            }
            break;
            case SpawnObjectType::DynamicSphere: {
                const auto mesh = std::make_shared<CircleMesh>(0.1f, 30);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(1.0, 0.5f, 0.2, new CircleCollisionShape(0.1f), true);
            }
            break;
            case SpawnObjectType::StaticSquare: {
                const auto mesh = std::make_shared<SquareMesh>(0.2f);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(0.0, 0.1f, 0.4, new BoxCollisionShape(0.2f, 0.2f), true);
            }
            break;
            case SpawnObjectType::DynamicSquare: {
                const auto mesh = std::make_shared<SquareMesh>(0.2f);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(1.0, 0.1f, 0.4, new BoxCollisionShape(0.2f, 0.2f), true);
            }
            break;
            default:
                break;
        }
    }
}

void key_callback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        Engine::clear_game_objects();
    }
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
