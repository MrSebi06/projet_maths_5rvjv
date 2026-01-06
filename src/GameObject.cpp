//
// Created by mihne on 01/12/2025.
//

#include "GameObject.h"

#include "Engine.h"
#include "Mesh/Circle/Circle.h"

void GameObject::enable() {
    enabled = true;
    Engine::physics.register_rigid_body(body.get());
}

void GameObject::disable() {
    enabled = false;
    Engine::physics.unregister_rigid_body(body.get());
}

void GameObject::draw() const {
    if (renderer == nullptr || !enabled) return;
    renderer->draw();
}

void GameObject::add_renderer(const std::shared_ptr<Mesh> &mesh, GLuint shader, const Vector3 &color) {
    renderer = std::make_unique<MeshRenderer>(mesh, shader, &transform, color);
}

void GameObject::add_rigidbody(const float &mass, const float &restitution, const float friction,
                               CollisionShape *shape, const bool debug) {
    body = std::make_unique<Rigidbody2D>(&transform, mass, restitution, friction, shape, debug);
    Engine::physics.register_rigid_body(body.get());
}
