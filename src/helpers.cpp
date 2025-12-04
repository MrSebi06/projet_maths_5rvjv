#include "helpers.h"

#include <fstream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>


double deg2rad(const double deg) {
    return deg * (PI / 180);
}

void set_aspect_ratio(const int width, const int height, const GLuint shader_program) {
    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    auto projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    glUseProgram(shader_program);
    const GLint proj_loc = glGetUniformLocation(shader_program, "projection");
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));
}

GLuint create_shader_program(const std::string &vert, const std::string &frag) {
    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    std::ifstream vertex_shader_file("shaders/" + vert);
    std::string vertex_shader_str((std::istreambuf_iterator(vertex_shader_file)),
                                  std::istreambuf_iterator<char>());
    const char *vertex_shader_source = vertex_shader_str.c_str();
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::ifstream fragment_shader_file("shaders/" + frag);
    std::string fragment_shader_str((std::istreambuf_iterator(fragment_shader_file)),
                                    std::istreambuf_iterator<char>());
    const char *fragment_shader_source = fragment_shader_str.c_str();
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    const GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << info_log << std::endl;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

Vector2 screen_to_world(const float mouseX, const float mouseY) {
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    const float aspect = static_cast<float>(width) / static_cast<float>(height);
    const float x = (2.0f * mouseX / static_cast<float>(width) - 1.0f) * aspect;
    const float y = 1.0f - 2.0f * mouseY / static_cast<float>(height);
    return {x, y};
}
