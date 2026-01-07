//
// Created by mihne on 04/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_INPUT_H
#define PROJET_MATHS_5RVJV_INPUT_H
#include <GLFW/glfw3.h>

void process_continuous_input(GLFWwindow *window, float dt);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif //PROJET_MATHS_5RVJV_INPUT_H
