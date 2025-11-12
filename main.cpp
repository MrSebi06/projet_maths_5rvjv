#include <chrono>

#include "init.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine.h"

#define WIDTH 800
#define HEIGHT 600

void process_input(GLFWwindow *window, const Engine *engine);

int main() {
    GLFW_config();
    GLFWwindow *window = create_window(WIDTH, HEIGHT);

    GLAD_init();

    const GLuint shader_program = create_shader_program("base.vert", "base.frag");
    glUseProgram(shader_program);
    setup_aspect_ratio(WIDTH, HEIGHT, shader_program);

    Engine engine;

    std::chrono::time_point<std::chrono::high_resolution_clock> last_tick = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window)) {
        process_input(window, &engine);

        // Calculate delta time using system clock
        const auto current_time = std::chrono::high_resolution_clock::now();
        const auto elapsed = current_time - last_tick;
        const auto elapsed_ms = duration_cast<std::chrono::microseconds>(elapsed);
        const float dt = elapsed_ms.count() / 1000000.0f;
        last_tick = current_time;

        engine.update(dt);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);

        engine.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader_program);

    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window, const Engine *engine) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        engine->emit_particle();

    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        engine->add_wind(Vector2(0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_LEFT))
        engine->add_wind(Vector2(-0.1f, 0));
    if (glfwGetKey(window, GLFW_KEY_UP))
        engine->add_wind(Vector2(0, 0.1f));
    if (glfwGetKey(window, GLFW_KEY_DOWN))
        engine->add_wind(Vector2(0, -0.1f));
}
