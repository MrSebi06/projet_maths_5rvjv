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
    renderer = std::make_unique<MeshRenderer>(mesh, shader, &transform, color);
}

Rigidbody2D *GameObject::add_rigidbody(const float &mass, const float &restitution, const float friction,
                                       Shape *shape) {
    body = new Rigidbody2D(&transform, mass, restitution, friction, shape);
    return body;
}
