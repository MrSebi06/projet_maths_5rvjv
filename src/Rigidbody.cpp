#include "Rigidbody.h"

Rigidbody2D::Rigidbody2D(Transform *transform, const float &mass, const float &restitution, Shape *shape)
    : transform(transform),
      shape(shape),
      restitution(restitution),
      mass(mass),
      angularVelocity(0),
      angularAcceleration(0), sumTorque(0) {
    // Mass == 0 means a static object
    invMass = mass == 0.0f ? 0.0f : 1 / mass;
    I = mass * shape->getMomentOfInertia();
    invI = 1 / I;
}

void Rigidbody2D::resetForces() {
    sumForces = Vector2();
    sumTorque = 0.0f;
}

void Rigidbody2D::impulse(const Vector2 &impulse) {
    if (invMass == 0.0f) return;
    velocity += impulse * invMass;
}

void Rigidbody2D::addForce(const Vector2 &force) {
    sumForces += force;
}

void Rigidbody2D::addTorque(const float torque) {
    sumTorque += torque;
}

void Rigidbody2D::integrate(const float dt) {
    // Acceleration is impacted by current forces...
    acceleration = sumForces * invMass;
    angularAcceleration = 0.0f; // ???

    // ...velocity is impacted by acceleration...
    velocity += acceleration * dt;
    angularVelocity += angularAcceleration * dt;

    // ...and position is impacted by velocity!
    transform->addPosition(velocity * dt);
    transform->addRotation(angularVelocity * dt);

    resetForces();
}
