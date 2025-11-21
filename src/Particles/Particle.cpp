//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include "Particles/Particle.h"

void Particle::addForce(const Vector2 &force) {
    sumForces = sumForces + force;
}

void Particle::resetForces() {
    sumForces = Vector2();
}

void Particle::integrate(const float &dt) {
    // Acceleration is impacted by current forces...
    acceleration = sumForces / mass;

    // ...velocity is impacted by acceleration...
    velocity += acceleration * dt;

    // ...and position is impacted by velocity!
    position += velocity * dt;

    resetForces();
}
