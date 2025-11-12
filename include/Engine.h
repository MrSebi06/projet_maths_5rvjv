//
// Created by mihne on 11/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_ENGINE_H
#define PROJET_MATHS_5RVJV_ENGINE_H
#include "PhysicsSystem.h"


class Engine {
    PhysicsSystem *physics_system;
    ParticleSystem *particle_system;

public:
    Engine() {
        physics_system = new PhysicsSystem();
        particle_system = new ParticleSystem();
    }

    void update(float dt) const;

    void draw() const;

    void emit_particle() const;
    void add_wind(const Vector2 &wind) const;
};


#endif //PROJET_MATHS_5RVJV_ENGINE_H
