//
// Created by Sacha TOUTUT on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_RIGIDBODY_H
#define PROJET_MATHS_5RVJV_RIGIDBODY_H

#include "Vector/Vector2.h"
#include "Shape.h"
#include "Mesh/Mesh.h"

class Rigidbody2D {
private:
public:
    float mass, invMass;
    Vector2 position, velocity, acceleration;
    Vector2 sumForces;

    float I, invI;
    float rotation, angularVelocity, angularAcceleration;
    float sumTorque;

    Shape* shape;
    Mesh* mesh;

    Rigidbody2D(const float& mass, Shape* shape, Mesh* mesh, const Vector2& position, const float& rotation);

    void draw();

    void resetForces();
    void addForce(Vector2 force);
    void addTorque(float torque);

    void integrate(float dt);
};

#endif //PROJET_MATHS_5RVJV_RIGIDBODY_H
