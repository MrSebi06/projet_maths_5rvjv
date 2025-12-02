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
    GameObject* gameObject;
    Shape* shape;

    float mass, invMass;
    Vector2 velocity, acceleration;
    Vector2 sumForces;

    float I, invI;
    float rotation, angularVelocity, angularAcceleration;
    float sumTorque;


    Rigidbody2D(GameObject* gameObject, const float& mass, Shape* shape, const float& rotation);

    void resetForces();
    void addForce(Vector2 force);
    void addTorque(float torque);

    void integrate(float dt);
};

#endif //PROJET_MATHS_5RVJV_RIGIDBODY_H
