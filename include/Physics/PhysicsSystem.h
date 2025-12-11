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

    void register_rigid_body(Rigidbody2D *body);
    void unregister_rigid_body(Rigidbody2D *body);
    void clear_bodies();
    void addPositionSticky(std::vector<int> excludedBodies, int bodyIndex, const Vector2& positionAdded) const;

    void add_wind(const Vector2 &wind_);
};

#endif //PROJET_MATHS_5RVJV_SIMULATION_H
