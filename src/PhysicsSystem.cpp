//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <PhysicsSystem.h>

#define GRAVITY Vector2(0, -9.81f)

void PhysicsSystem::update(const float dt) {
    // Go through every rigidbody and softbody and apply physics
}

void PhysicsSystem::add_wind(const Vector2 &wind_) {
    wind += wind_;
}


