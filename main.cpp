#include "init.h"
#include "src/Mesh.h"


void process_input(GLFWwindow *window);


int main() {
    GLFW_config();
    GLFWwindow *window = create_window(800, 600);

    GLAD_init();

    const GLuint shader_program = create_shader_program("base.vert", "base.frag");

    constexpr GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
    constexpr GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    auto mesh = create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);

        mesh.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    mesh.cleanup();
    glDeleteProgram(shader_program);

    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
