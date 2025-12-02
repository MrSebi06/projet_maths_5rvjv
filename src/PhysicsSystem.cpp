//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <PhysicsSystem.h>

#include "Engine.h"

#define GRAVITY Vector2(0, -9.81f)

void PhysicsSystem::update(const float dt) const {
    Engine::particles.add_force(wind);
    Engine::particles.add_force(GRAVITY);

    for (const auto body: bodies) {
        body->addForce(wind);
        body->addForce(GRAVITY);

        body->integrate(dt);
    }

    // After the basic physics update, resolve collisions
    for (int i = 0; i < bodies.size(); ++i) {
        Rigidbody2D *currentBody = bodies[i];

        // TODO: Implement broad detection first to optimize
        for (int j = i + 1; j < bodies.size(); ++j) {
            CollisionDetection::CollisionInfo info;
            if (CollisionDetection::is_colliding(currentBody, bodies[j], info))
                CollisionDetection::resolve_collision(info);
        }
    }
}

void PhysicsSystem::registerRigidBody(GameObject *gameObject, const float &mass, const float &restitution,
                                      const float friction,
                                      Shape *shape) {
    bodies.push_back(gameObject->add_rigidbody(mass, restitution, friction, shape));
}

void PhysicsSystem::add_wind(const Vector2 &wind_) {
    wind += wind_;
}



