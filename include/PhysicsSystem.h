//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_SIMULATION_H
#define PROJET_MATHS_5RVJV_SIMULATION_H

#include "Particles/ParticleSystem.h"
#include "Rigidbody.h"
#include "CollisionDetection.h"

class PhysicsSystem {
private:
    std::vector<Rigidbody2D*> bodies;

public:
    Vector2 wind;

    PhysicsSystem() = default;

    void update(float dt) const;
    void registerRigidBody(GameObject* gameObject, const float& mass, Shape* shape, const float& rotation);

    void add_wind(const Vector2 &wind_);
};

#endif //PROJET_MATHS_5RVJV_SIMULATION_H
