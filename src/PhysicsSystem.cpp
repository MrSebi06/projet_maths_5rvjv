//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <PhysicsSystem.h>

#include "Engine.h"

#define GRAVITY Vector2(0, -9.81f)

void PhysicsSystem::update(const float dt) const {
    Engine::particles.add_force(wind);
    Engine::particles.add_force(GRAVITY);

    // Ideally: go through every rigidbody and softbody and apply physics
    for (int i = 0; i < Engine::objects.size(); ++i)
    {
        Rigidbody2D* body = Engine::objects[i];
        body->addForce(wind);
        body->addForce(GRAVITY);
    }
}

void PhysicsSystem::add_wind(const Vector2 &wind_) {
    wind += wind_;
}



