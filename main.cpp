#include <chrono>
#include <cmath>
#include <random>

#include "init.h"

#include "Engine.h"

#define WIDTH 800
#define HEIGHT 600
#define ASPECT_RATIO (static_cast<float>(WIDTH) / static_cast<float>(HEIGHT))

void process_input(GLFWwindow *window);
Vector2 screen_to_world(float mouseX, float mouseY);

int main() {
    std::srand(std::time({}));

    GLFW_config();
    GLFWwindow *window = create_window(WIDTH, HEIGHT);

    GLAD_init();

    const GLuint shader_program = create_shader_program("base.vert", "base.frag");
    glUseProgram(shader_program);
    setup_aspect_ratio(WIDTH, HEIGHT, shader_program);

    Engine::init();

    std::chrono::time_point<std::chrono::high_resolution_clock> last_tick = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        // Calculate delta time using system clock
        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto elapsed = current_time - last_tick;
        const auto elapsed_ms = duration_cast<std::chrono::microseconds>(elapsed);
        const float dt = elapsed_ms.count() / 1000000.0f;
        last_tick = current_time;

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

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution angle_dist(-1.0f, 1.0f);
        static std::uniform_real_distribution speed_dist(0.2f, 1.0f);
        const Vector2 velocity(speed_dist(gen) * angle_dist(gen), speed_dist(gen) * angle_dist(gen));

        static std::uniform_real_distribution lifetime_dist(0.05f, 0.3f);

        Engine::particles.emit(screen_to_world(xpos, ypos),
                               lifetime_dist(gen),
                               velocity
        );
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        Engine::physics.add_wind(Vector2(0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_LEFT))
        Engine::physics.add_wind(Vector2(-0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_UP))
        Engine::physics.add_wind(Vector2(0, 0.1f));
    if (glfwGetKey(window, GLFW_KEY_DOWN))
        Engine::physics.add_wind(Vector2(0, -0.1f));
}

Vector2 screen_to_world(const float mouseX, const float mouseY) {
    const float x = (2.0f * mouseX / WIDTH - 1.0f) * ASPECT_RATIO;
    const float y = 1.0f - 2.0f * mouseY / HEIGHT;
    return {x, y};
}
