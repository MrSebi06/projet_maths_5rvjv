#ifndef PROJET_MATHS_5RVJV_HELPERS_H
#define PROJET_MATHS_5RVJV_HELPERS_H

#define PI 3.14159

#include "glad/glad.h"
#include "Vector/Vector2.h"
#include <string>
#include <GLFW/glfw3.h>

double deg2rad(double deg);
void set_aspect_ratio(int width, int height, GLuint shader_program);
GLuint create_shader_program(const std::string &vert, const std::string &frag);
Vector2 screen_to_world(GLFWwindow *window, float mouseX, float mouseY);

#endif //PROJET_MATHS_5RVJV_HELPERS_H
