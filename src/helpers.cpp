#include "helpers.h"

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
