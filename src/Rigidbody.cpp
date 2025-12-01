#include "Rigidbody.h"

Rigidbody2D::Rigidbody2D(const float &mass, Shape* shape, Mesh* mesh, const Vector2 &position, const float &rotation)
    : mass(mass), shape(shape), mesh(mesh), position(position), rotation(rotation)
{
    invMass = 1 / mass;
    I = mass * shape->getMomentOfInertia();
    invI = 1 / I;
}

void Rigidbody2D::draw()
{
    mesh->draw(&position);
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
    position += velocity * dt;
    rotation += angularVelocity * dt;

    resetForces();
}
