//
// Created by Sacha TOUTUT on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_RIGIDBODY_H
#define PROJET_MATHS_5RVJV_RIGIDBODY_H

#include "Vector/Vector2.h"
#include "CollisionShape.h"
#include "Mesh/Mesh.h"
#include "GameObject.h"

class Rigidbody2D {
public:
    Transform *transform;
    CollisionShape *shape;

    float restitution;
    float friction;

    float mass, invMass;
    Vector2 velocity, acceleration;
    Vector2 sumForces;

    float I, invI;
    float angularVelocity, angularAcceleration;
    float sumTorque;


    Rigidbody2D(Transform *transform, const float &mass, const float &restitution, float friction, CollisionShape *shape);

    void resetForces();
    void impulse(const Vector2 &impulse, const Vector2 &rotation = {0.0f, 0.0f});
    void addForce(const Vector2 &force);
    void addTorque(float torque);

    void integrate(float dt);
};

#endif //PROJET_MATHS_5RVJV_RIGIDBODY_H
