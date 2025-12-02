//
// Created by mihne on 01/12/2025.
//

#include "GameObject.h"

#include "Engine.h"
#include "Mesh/Circle/Circle.h"

void GameObject::draw() const {
    if (renderer == nullptr) return;
    renderer->draw();
}

void GameObject::add_renderer(const std::shared_ptr<Mesh> &mesh, GLuint shader, const Vector3 &color) {
    renderer = std::make_unique<MeshRenderer>(mesh, shader, &position, color);
}

Rigidbody2D* GameObject::add_rigidbody(const float &mass, const float& restitution, Shape *shape, const float &rotation)
{
    body = new Rigidbody2D(&position, mass, restitution, shape, rotation);
    return body;
}
