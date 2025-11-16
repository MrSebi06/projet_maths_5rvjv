//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_SIMULATION_H
#define PROJET_MATHS_5RVJV_SIMULATION_H

#include <vector>
#include <Particle.h>
#include <chrono>

#include "ParticleSystem.h"

class Simulation {
    std::chrono::time_point<std::chrono::high_resolution_clock> last_tick;

    std::vector<ParticleSystem *> particle_systems;

public:
    Vector2 wind;

    Simulation() : last_tick(std::chrono::high_resolution_clock::now()),
                   particle_systems(std::vector<ParticleSystem *>()),
                   wind() {}

    void update();
    void draw() const;

    void register_particle_system(ParticleSystem *p) {
        particle_systems.push_back(p);
    }
};

#endif //PROJET_MATHS_5RVJV_SIMULATION_H
