#include "Rigidbody.h"

Rigidbody2D::Rigidbody2D(Vector2* transform, const float &mass, Shape* shape, const float &rotation)
    : transform(transform), mass(mass), shape(shape), rotation(rotation)
{
    // Mass == 0 means a static object
    invMass = mass == 0.0f ? 0.0f : 1 / mass;
    I = mass * shape->getMomentOfInertia();
    invI = 1 / I;
}

void Rigidbody2D::resetForces()
{
    sumForces = Vector2();
    sumTorque = 0.0f;
}

void Rigidbody2D::addForce(Vector2 force)
{
    sumForces += force;
}

void Rigidbody2D::addTorque(float torque)
{
    sumTorque += torque;
}

void Rigidbody2D::integrate(float dt) {
    // Acceleration is impacted by current forces...
    acceleration = sumForces / mass;
    angularAcceleration = 0.0f; // ???

    // ...velocity is impacted by acceleration...
    velocity += acceleration * dt;
    angularVelocity += angularAcceleration * dt;

    // ...and position is impacted by velocity!
    *transform += velocity * dt;
    rotation += angularVelocity * dt;

    resetForces();
}
