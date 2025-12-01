//
// Created by mihne on 01/12/2025.
//

#include "GameObject.h"

#include "Engine.h"
#include "Mesh/Circle/Circle.h"

void GameObject::draw() const {
    renderer->draw();
}

void GameObject::add_renderer(const std::shared_ptr<Mesh> &mesh, GLuint shader, const Vector3 &color) {
    renderer = std::make_unique<MeshRenderer>(mesh, shader, &position, color);
}
