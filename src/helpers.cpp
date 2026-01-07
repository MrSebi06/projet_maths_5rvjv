#include "helpers.h"

#include <fstream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "Globals.h"
#include "init.h"


double deg2rad(const double deg) {
    return deg * (PI / 180);
}

void set_aspect_ratio(const int width, const int height, const GLuint shader_program) {
    const float world_width = width / WORLD_SCALE;
    const float world_height = height / WORLD_SCALE;

    glm::mat4 projection = glm::ortho(
        0.0f, world_width,
        0.0f, world_height,
        -1.0f, 1.0f
    );

    glUseProgram(shader_program);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
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


Vector2 screen_to_world(GLFWwindow *window, float screen_x, float screen_y) {
    const Shaders shaders = *static_cast<Shaders *>(glfwGetWindowUserPointer(window));

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Screen to pixels, flip Y
    float pixel_x = screen_x;
    float pixel_y = height - screen_y;

    // Pixels to world units
    float world_x = pixel_x / WORLD_SCALE;
    float world_y = pixel_y / WORLD_SCALE;

    // Undo view transform
    world_x = world_x / shaders.camera_zoom + shaders.camera_pos.x;
    world_y = world_y / shaders.camera_zoom + shaders.camera_pos.y;

    return {world_x, world_y};
}
