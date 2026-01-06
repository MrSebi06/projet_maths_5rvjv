//
// Created by Sacha TOUTUT on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_RIGIDBODY_H
#define PROJET_MATHS_5RVJV_RIGIDBODY_H

#include "Vector/Vector2.h"
#include "CollisionShape.h"
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

    std::unique_ptr<MeshRenderer> debug_renderer = nullptr;

    Rigidbody2D(Transform *transform, const float &mass, const float &restitution, float friction,
                CollisionShape *shape, bool debug = false);

    void reset_forces();
    void add_force(const Vector2 &force);
    void add_torque(float torque);
    void impulse(const Vector2 &impulse, const Vector2 &rotation = {0.0f, 0.0f});

    virtual void integrate(float dt);
};

#endif //PROJET_MATHS_5RVJV_RIGIDBODY_H
