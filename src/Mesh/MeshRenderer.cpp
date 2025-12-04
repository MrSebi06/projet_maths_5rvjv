//
// Created by mihne on 01/12/2025.
//

#include "Mesh/MeshRenderer.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

#include "Transform.h"

void MeshRenderer::draw() const {
    if (mesh == nullptr) return;

    glUseProgram(shader_program);

    if (debug)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto model = glm::mat4(1.0f);
    const Vector2 pos = transform->getPosition();
    model = glm::translate(model, glm::vec3(pos.getX(), pos.getY(), 0.0f));
    model = glm::rotate(model, transform->getRotation(), glm::vec3(0.0, 0.0, 1.0));
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(model));

    glUniform3f(loc_color, color.x, color.y, color.z);

    mesh->bind();
    glDrawElements(GL_TRIANGLES, mesh->get_index_count(), GL_UNSIGNED_INT, nullptr);
    mesh->unbind();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
