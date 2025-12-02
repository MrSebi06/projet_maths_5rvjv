#include <chrono>
#include <random>

#include "init.h"

#include "Engine.h"
#include "GameObject.h"
#include "Particles/Emitters/LiquidStreamEmitter.h"
#include "Particles/Emitters/SparkleEmitter.h"

#define WIDTH 800
#define HEIGHT 600
#define ASPECT_RATIO (static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))


enum class EmitterType {
    Sparkle,
    LiquidStream
};

auto current_emitter_type = EmitterType::Sparkle;

void process_continuous_input(GLFWwindow *window, const float dt);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
Vector2 screen_to_world(float mouseX, float mouseY);
void window_size_callback(GLFWwindow *window, int width, int height);

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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    std::chrono::time_point<std::chrono::high_resolution_clock> last_tick = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time using system clock
        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto elapsed = current_time - last_tick;
        const auto elapsed_ms = duration_cast<std::chrono::microseconds>(elapsed);
        const float dt = elapsed_ms.count() / 1000000.0f;
        last_tick = current_time;

        process_continuous_input(window, dt);
        Engine::update(dt);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Engine::draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(particle_shader_program);

    glfwTerminate();

    return 0;
}


void process_continuous_input(GLFWwindow *window, const float dt) {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        const Vector2 pos = screen_to_world(static_cast<float>(xpos), static_cast<float>(ypos));
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
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(-0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(0, 0.1f));
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        Engine::physics.add_wind(Vector2(0, -0.1f));
}

void key_callback(GLFWwindow *window, const int key, int scancode, int action, int mods) {
    const Shaders shaders = *static_cast<Shaders *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        // Switch between liquid and sparkle emitters
        current_emitter_type = (current_emitter_type == EmitterType::Sparkle)
                                   ? EmitterType::LiquidStream
                                   : EmitterType::Sparkle;
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        const Vector2 pos = screen_to_world(static_cast<float>(xpos), static_cast<float>(ypos));

        const auto circle_mesh = std::make_shared<Circle>(0.1f, 30);
        const auto player = Engine::create_game_object(pos);
        player->add_renderer(circle_mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
        Engine::physics.registerRigidBody(player, 1.0, 1.0, 0.5, new CircleShape(0.1f));
    }

    if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        const Vector2 pos = screen_to_world(static_cast<float>(xpos), static_cast<float>(ypos));

        const auto circle_mesh = std::make_shared<Circle>(0.1f, 30);
        const auto player = Engine::create_game_object(pos);
        player->add_renderer(circle_mesh, shaders.base_shader_program, Vector3{1.0f, 0.0f, 0.0f});
        Engine::physics.registerRigidBody(player, 0.0, 0.5f, 0.5, new CircleShape(0.1f));
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Vector2 screen_to_world(const float mouseX, const float mouseY) {
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    const float x = (2.0f * mouseX / width - 1.0f) * aspect;
    const float y = 1.0f - 2.0f * mouseY / height;
    return {x, y};
}

void window_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
    const Shaders shaders = *static_cast<Shaders *>(glfwGetWindowUserPointer(window));
    set_aspect_ratio(width, height, shaders.particle_shader_program);
    set_aspect_ratio(width, height, shaders.base_shader_program);
}
