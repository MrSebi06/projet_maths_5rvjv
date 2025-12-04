//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_SIMULATION_H
#define PROJET_MATHS_5RVJV_SIMULATION_H
#include <vector>

#include "Vector/Vector2.h"
#include "GameObject.h"

class Rigidbody2D;
struct CollisionShape;


class PhysicsSystem {
    std::vector<Rigidbody2D *> bodies;

public:
    Vector2 wind;

    PhysicsSystem() = default;

    void update(float dt) const;
    void registerRigidBody(GameObject *gameObject,
                           const float &mass,
                           const float &restitution,
                           float friction,
                           CollisionShape *shape, bool debug = false);

    void add_wind(const Vector2 &wind_);
};

#endif //PROJET_MATHS_5RVJV_SIMULATION_H
