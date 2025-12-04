#include "../../include/Physics/Rigidbody.h"

Rigidbody2D::Rigidbody2D(Transform *transform, const float &mass, const float &restitution, const float friction,
                         Shape *shape)
    : transform(transform),
      shape(shape),
      restitution(restitution), friction(friction),
      mass(mass),
      angularVelocity(0),
      angularAcceleration(0), sumTorque(0) {
    // Mass == 0 means a static object
    invMass = mass == 0.0f ? 0.0f : 1 / mass;
    I = mass * shape->getMomentOfInertia();
    invI = I == 0.0f ? 0.0f : 1 / I;
}

void Rigidbody2D::resetForces() {
    sumForces = Vector2();
    sumTorque = 0.0f;
}

void Rigidbody2D::impulse(const Vector2 &impulse, const Vector2 &rotation
) {
    if (invMass == 0.0f) return;
    velocity += impulse * invMass;
    angularVelocity += rotation.cross(impulse) * invI;
}

void Rigidbody2D::addForce(const Vector2 &force) {
    sumForces += force;
}

void Rigidbody2D::addTorque(const float torque) {
    sumTorque += torque;
}

void Rigidbody2D::integrate(const float dt) {
    if (mass == 0.0f) return;

    // Acceleration is impacted by current forces...
    acceleration = sumForces * invMass;
    angularAcceleration = sumTorque * invI;

    // ...velocity is impacted by acceleration...
    velocity += acceleration * dt;
    angularVelocity += angularAcceleration * dt;

    // ...and position is impacted by velocity!
    transform->addPosition(velocity * dt);
    transform->addRotation(angularVelocity * dt);

    resetForces();
}
