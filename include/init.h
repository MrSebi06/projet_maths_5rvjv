#ifndef PROJET_MATHS_INIT_H
#define PROJET_MATHS_INIT_H

#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "glad/glad.h"

void GLFW_config();

GLFWwindow *create_window(int width, int height);

void GLAD_init();

GLuint create_shader_program(const std::string &vert, const std::string &frag);


#endif //PROJET_MATHS_INIT_H
