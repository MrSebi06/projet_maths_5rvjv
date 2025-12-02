//
// Created by Sacha TOUTUT on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_RIGIDBODY_H
#define PROJET_MATHS_5RVJV_RIGIDBODY_H

#include "Vector/Vector2.h"
#include "Shape.h"
#include "Mesh/Mesh.h"
#include "GameObject.h"

class Rigidbody2D {
public:
    // TODO: P L E A S E STOP REWRITING THIS AND JUST USE A TRANSFORM COMPONENT
    Vector2* transform;
    Shape* shape;

    float restitution;

    float mass, invMass;
    Vector2 velocity, acceleration;
    Vector2 sumForces;

    float I, invI;
    float rotation, angularVelocity, angularAcceleration;
    float sumTorque;


    Rigidbody2D(Vector2* transform, const float& mass, const float& restitution, Shape* shape, const float& rotation);

    void resetForces();
    void impulse(const Vector2& impulse);
    void addForce(Vector2 force);
    void addTorque(float torque);

    void integrate(float dt);
};

#endif //PROJET_MATHS_5RVJV_RIGIDBODY_H
