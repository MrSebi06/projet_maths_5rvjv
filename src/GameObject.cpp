//
// Created by mihne on 01/12/2025.
//

#include "GameObject.h"

#include <algorithm>

#include "Engine.h"
#include "Mesh/Circle/Circle.h"
#include "Physics/LiquidBody.h"

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
    if (velocity_color) {
        constexpr float max_vel = 4.0f;
        const float current_vel = body.get()->velocity.magnitude();
        const Vector3 color = {
            std::ranges::clamp((start_vel_color.x + current_vel) / max_vel, start_vel_color.x, end_vel_color.x),
            std::ranges::clamp((start_vel_color.x + current_vel) / max_vel, start_vel_color.y, end_vel_color.y),
            std::ranges::clamp((start_vel_color.x + current_vel) / max_vel, start_vel_color.z, end_vel_color.z),
        };

        renderer->set_color(color);
    }
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

void GameObject::add_liquidbody(const float &mass, const float &restitution, const float friction,
                                CollisionShape *shape, const bool debug) {
    body = std::make_unique<LiquidBody>(&transform, mass, restitution, friction, shape, debug);
    Engine::physics.register_rigid_body(body.get());
}

void GameObject::enable_velocity_color(const Vector3 &start, const Vector3 &end) {
    velocity_color = true;
    start_vel_color = start;
    end_vel_color = end;
}

