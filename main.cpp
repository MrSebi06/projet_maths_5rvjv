#include <chrono>
#include <random>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "init.h"
#include "input.h"

#include "imgui-1.92.5/backends/imgui_impl_glfw.h"
#include "imgui-1.92.5/backends/imgui_impl_opengl3.h"
#include "Engine.h"
#include "Globals.h"
#include "include/Physics/PhysicsEmitter.h"
#include "Mesh/Polygon/Rect.h"
#include "Mesh/Polygon/Square.h"
#include "Particles/Emitters/LiquidStreamEmitter.h"
#include "Particles/Emitters/SparkleEmitter.h"
#include "Physics/CollisionShape.h"

enum class EmitterType {
    Sparkle,
    LiquidStream,
    PhysicsLiquid
};

enum class SpawnObjectType {
    Particles,

    StaticSphere,
    DynamicSphere,

    StaticSquare,
    DynamicSquare,

    Water
};


auto current_emitter_type = EmitterType::Sparkle;
auto current_spawn_object_type = SpawnObjectType::Particles;
std::vector<GameObject *> environment;

void draw_ui();

int main() {
    std::srand(std::time({}));

    GLFWwindow *window = GLFW_init(800, 600);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

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

    // Environment
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    const auto floor_mesh = std::make_shared<RectMesh>(8, 0.5f);
    const auto floor = Engine::create_game_object({4, 0.1f}, 0);
    floor->add_renderer(floor_mesh, shaders.base_shader_program, Vector3{0.1});
    floor->add_rigidbody(0.0, 0.5f, 0.4, new BoxCollisionShape(8, 0.5f), false);
    floor->name = "Floor";
    environment.push_back(floor);

    const auto right_wall_mesh = std::make_shared<RectMesh>(0.5f, 6);
    const auto right_wall = Engine::create_game_object({8, 3}, 0);
    right_wall->add_renderer(right_wall_mesh, shaders.base_shader_program, Vector3{0.1});
    right_wall->add_rigidbody(0.0, 0.5f, 0.4, new BoxCollisionShape(0.5f, 6), false);
    right_wall->name = "Right wall";
    environment.push_back(right_wall);

    const auto left_wall_mesh = std::make_shared<RectMesh>(0.5f, 6);
    const auto left_wall = Engine::create_game_object({0, 3}, 0);
    left_wall->add_renderer(left_wall_mesh, shaders.base_shader_program, Vector3{0.1});
    left_wall->add_rigidbody(0.0, 0.5f, 0.4, new BoxCollisionShape(0.5f, 6), false);
    left_wall->name = "Left wall";
    environment.push_back(left_wall);


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

        // Camera
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::scale(view, glm::vec3(shaders.camera_zoom, shaders.camera_zoom, 1.0f));
        view = glm::translate(view, glm::vec3(-shaders.camera_pos.x, -shaders.camera_pos.y, 0.0f));
        glUseProgram(base_shader_program);
        glUniformMatrix4fv(glGetUniformLocation(base_shader_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUseProgram(particle_shader_program);
        glUniformMatrix4fv(glGetUniformLocation(particle_shader_program, "view"), 1, GL_FALSE, glm::value_ptr(view));

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
    static bool was_dragging = false;
    static bool was_emitting = false;
    static Emitter *current_emitter = nullptr;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    const Vector2 pos = screen_to_world(window, static_cast<float>(xpos), static_cast<float>(ypos));

    auto *shaders = static_cast<Shaders *>(glfwGetWindowUserPointer(window));

    if (current_spawn_object_type == SpawnObjectType::Particles) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
            if (!was_emitting) {
                // First frame of click - create emitter
                switch (current_emitter_type) {
                    case EmitterType::Sparkle:
                        current_emitter = new SparkleEmitter(pos);
                        break;
                    case EmitterType::LiquidStream:
                        current_emitter = new LiquidStreamEmitter(pos);
                        break;
                    case EmitterType::PhysicsLiquid:
                        current_emitter = new PhysicsEmitter(pos, shaders->base_shader_program, 0.1f, 0.1f, 0.01f,
                                                             new CircleCollisionShape(0.05f), false, true);
                        break;
                }
                current_emitter->start();
            } else {
                current_emitter->set_position(pos);
            }
            was_emitting = true;
        } else if (was_emitting) {
            // Just released
            current_emitter->stop();
            current_emitter = nullptr;
            was_emitting = false;
        }
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse) {
        static Vector2 last_screen_pos = {0, 0};
        Vector2 current_screen = {static_cast<float>(xpos), static_cast<float>(ypos)};

        if (was_dragging) {
            Vector2 delta = {current_screen.x - last_screen_pos.x, current_screen.y - last_screen_pos.y};

            shaders->camera_pos.x -= delta.x / shaders->camera_zoom / WORLD_SCALE;
            shaders->camera_pos.y += delta.y / shaders->camera_zoom / WORLD_SCALE;
        }
        was_dragging = true;
        last_screen_pos = current_screen;
    } else {
        was_dragging = false;
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
        const Vector2 pos = screen_to_world(window, static_cast<float>(xpos), static_cast<float>(ypos));

        switch (current_spawn_object_type) {
            case SpawnObjectType::StaticSphere: {
                const auto mesh = std::make_shared<CircleMesh>(0.1f, 30);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(0.0, 0.5f, 0.2, new CircleCollisionShape(0.1f), false);
            }
            break;
            case SpawnObjectType::DynamicSphere: {
                const auto mesh = std::make_shared<CircleMesh>(0.1f, 30);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(1.0, 0.5f, 0.2, new CircleCollisionShape(0.1f), false);
            }
            break;
            case SpawnObjectType::StaticSquare: {
                const auto mesh = std::make_shared<SquareMesh>(0.2f);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(0.0, 0.4f, 0.4, new BoxCollisionShape(0.2f, 0.2f), false);
            }
            break;
            case SpawnObjectType::DynamicSquare: {
                const auto mesh = std::make_shared<SquareMesh>(0.2f);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
                game_object->add_rigidbody(1.0, 0.4f, 0.4, new BoxCollisionShape(0.2f, 0.2f), false);
            }
            break;
            case SpawnObjectType::Water: {
                const auto mesh = std::make_shared<CircleMesh>(0.05f, 20);
                const auto game_object = Engine::create_game_object(pos);
                game_object->add_renderer(mesh, shaders.base_shader_program, Vector3(0.0f, 0.0f, 1.0f));
                game_object->add_liquidbody(0.1f, 0.1f, 0.01f, new CircleCollisionShape(0.05f));
            }
            default:
                break;
        }
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    auto *shaders = static_cast<Shaders *>(glfwGetWindowUserPointer(window));

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    Vector2 world_before = screen_to_world(window, static_cast<float>(xpos), static_cast<float>(ypos));

    shaders->camera_zoom *= (yoffset > 0) ? 1.1f : 0.9f;
    shaders->camera_zoom = std::clamp(shaders->camera_zoom, 0.1f, 10.0f);

    Vector2 world_after = screen_to_world(window, static_cast<float>(xpos), static_cast<float>(ypos));

    // Adjust camera so the same world point stays under cursor
    shaders->camera_pos.x += world_before.x - world_after.x;
    shaders->camera_pos.y += world_before.y - world_after.y;
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

    const char *particles[] = {"Sparkles", "Particle Liquid", "Physics Water"};
    if (ImGui::BeginListBox("Particle emitters",
                            ImVec2(
                                0, ImGui::GetTextLineHeightWithSpacing() * IM_ARRAYSIZE(particles) + ImGui::GetStyle().
                                   FramePadding.y * 2))
    ) {
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

    const char *spawn_objects[] = {
        "Particles", "StaticSphere", "DynamicSphere", "StaticSquare", "DynamicSquare", "Water"
    };
    if (ImGui::BeginListBox("Objects to spawn",
                            ImVec2(
                                0, ImGui::GetTextLineHeightWithSpacing() * IM_ARRAYSIZE(spawn_objects) +
                                   ImGui::GetStyle().FramePadding.y * 2))
    ) {
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

    if (ImGui::BeginListBox("Environment",
                            ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * (environment.size() + 1.5)))) {
        for (const auto &e: environment) {
            bool is_enabled = e->isEnabled();
            if (ImGui::Checkbox(e->name.value_or("Unnamed").c_str(), &is_enabled)) {
                if (is_enabled) e->enable();
                else e->disable();
            }
        }
        ImGui::EndListBox();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
