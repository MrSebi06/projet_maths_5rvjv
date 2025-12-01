//
// Created by mihne on 01/12/2025.
//

#include "Mesh/MeshRenderer.h"

void MeshRenderer::draw() const {
    if (mesh == nullptr) return;

    glUseProgram(shader_program);
    glUniform2f(loc_offset, position->x, position->y);
    glUniform3f(loc_color, color.x, color.y, color.z);

    mesh->bind();
    glDrawElements(GL_TRIANGLES, mesh->get_index_count(), GL_UNSIGNED_INT, nullptr);
    mesh->unbind();
}
