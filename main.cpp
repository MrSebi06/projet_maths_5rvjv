#include <chrono>
#include <random>

#include "init.h"

#include "Engine.h"
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

int main() {
    std::srand(std::time({}));

    GLFW_config();
    GLFWwindow *window = create_window(WIDTH, HEIGHT);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    GLAD_init();

    const GLuint shader_program = create_shader_program("base.vert", "base.frag");
    glUseProgram(shader_program);
    setup_aspect_ratio(WIDTH, HEIGHT, shader_program);

    Engine::init();

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
        glUseProgram(shader_program);

        Engine::draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader_program);

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
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        // Switch between liquid and sparkle emitters
        current_emitter_type = (current_emitter_type == EmitterType::Sparkle)
                                   ? EmitterType::LiquidStream
                                   : EmitterType::Sparkle;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Vector2 screen_to_world(const float mouseX, const float mouseY) {
    const float x = (2.0f * mouseX / WIDTH - 1.0f) * ASPECT_RATIO;
    const float y = 1.0f - 2.0f * mouseY / HEIGHT;
    return {x, y};
}
