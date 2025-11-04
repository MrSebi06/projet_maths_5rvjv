//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_SIMULATION_H
#define PROJET_MATHS_5RVJV_SIMULATION_H

#include <vector>
#include <Particle.h>
#include <chrono>

class Simulation {
private:
    std::vector<Particle> particles;
    std::chrono::time_point<std::chrono::high_resolution_clock> last_tick;

public:
    Simulation() : particles(std::vector<Particle>()), last_tick(std::chrono::high_resolution_clock::now()) {}

    void update();
    void draw();

    void addParticle(const Vector2& pos);
};

#endif //PROJET_MATHS_5RVJV_SIMULATION_H
