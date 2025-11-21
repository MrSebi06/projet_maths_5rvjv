//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_SIMULATION_H
#define PROJET_MATHS_5RVJV_SIMULATION_H

#include "ParticleSystem.h"

class PhysicsSystem {
public:
    Vector2 wind;

    PhysicsSystem() = default;

    void update(float dt) const;

    void add_wind(const Vector2 &wind_);
};

#endif //PROJET_MATHS_5RVJV_SIMULATION_H
