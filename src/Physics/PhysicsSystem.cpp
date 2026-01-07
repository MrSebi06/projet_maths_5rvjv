//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <Physics/PhysicsSystem.h>

#include <Engine.h>
#include <Physics/CollisionDetection.h>
#include <algorithm>
#include <ranges>
#include "Physics/PhysicsEmitter.h"

#include "Globals.h"

#define GRAVITY Vector2(0, -9.81f * WORLD_SCALE)

void PhysicsSystem::update(const float dt) const {
    Engine::particles.add_force(wind);
    Engine::particles.add_force(GRAVITY);

    for (const auto emitter: emitters | std::views::values) {
        emitter->update(dt);
    }

    for (const auto body: bodies) {
        body->add_force(wind);
        body->add_force(GRAVITY * body->mass);

        body->integrate(dt);
    }

    // After the basic physics update, resolve collisions
    for (int i = 0; i < bodies.size(); ++i) {
        Rigidbody2D *currentBody = bodies[i];

        for (int j = i + 1; j < bodies.size(); ++j) {
            CollisionDetection::CollisionInfo info;
            if (CollisionDetection::is_colliding(currentBody, bodies[j], info))
                CollisionDetection::resolve_collision(info);
        }
    }
}

void PhysicsSystem::register_rigid_body(Rigidbody2D *body) {
    bodies.push_back(body);
}

void PhysicsSystem::unregister_rigid_body(Rigidbody2D *body) {
    bodies.erase(std::ranges::remove(bodies, body).begin(), bodies.end());
}

void PhysicsSystem::clear_bodies() {
    bodies.clear();
}


void PhysicsSystem::register_emitter(PhysicsEmitter *emitter) {
    emitters.insert({reinterpret_cast<size_t>(emitter), emitter});
}

void PhysicsSystem::add_wind(const Vector2 &wind_) {
    wind += wind_;
}




