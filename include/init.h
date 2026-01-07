#ifndef PROJET_MATHS_INIT_H
#define PROJET_MATHS_INIT_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "glad/glad.h"
#include "Vector/Vector2.h"


struct Shaders {
    GLuint particle_shader_program;
    GLuint base_shader_program;
    float camera_zoom = 1.0f;
    Vector2 camera_pos = {0, 0};
};

GLFWwindow *GLFW_init(int width, int height);

void GLAD_init();

void IMGUI_init(GLFWwindow *window);


#endif //PROJET_MATHS_INIT_H
