#include "init.h"
#include "include/Mesh/Mesh.h"
#include "Mesh/Circle/Circle.h"
#include "Simulation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void process_input(GLFWwindow *window, Simulation &sim, ParticleSystem &ps);

int main() {
    GLFW_config();
    GLFWwindow *window = create_window(800, 600);

    constexpr float aspect = 800.0f / 600.0f;
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

    GLAD_init();

    const GLuint shader_program = create_shader_program("base.vert", "base.frag");
    glUseProgram(shader_program);

    const GLint projLoc = glGetUniformLocation(shader_program, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


    // Initialize simulation
    Simulation sim;
    ParticleSystem ps;
    sim.register_particle_system(&ps);
    // for (const auto &particle: sim.getParticles()) {
    //     particle.mesh->assign_shader(shader_program);
    // }

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        process_input(window, sim, ps);

        // Step simulation forward
        sim.update();

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);

        sim.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader_program);

    glfwTerminate();

    return 0;
}

void process_input(GLFWwindow *window, Simulation &sim, ParticleSystem &ps) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        ps.emit();

    if (glfwGetKey(window, GLFW_KEY_RIGHT))
        sim.wind += Vector2(0.1f, 0);
    if (glfwGetKey(window, GLFW_KEY_LEFT))
        sim.wind += Vector2(-0.1f, 0);
    if (glfwGetKey(window, GLFW_KEY_UP))
        sim.wind += Vector2(0, -0.1f);
    if (glfwGetKey(window, GLFW_KEY_DOWN))
        sim.wind += Vector2(0, 0.1f);
}
