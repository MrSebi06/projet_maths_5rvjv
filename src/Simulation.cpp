//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <Simulation.h>
#include <iostream>

void Simulation::update() {
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed = current_time - last_tick;
    auto elapsed_ms = duration_cast<std::chrono::milliseconds>(elapsed);
    float dt = elapsed_ms.count() / 1000.0f;

    std::cout << dt << std::endl;
    for (int i = 0; i < particles.size(); ++i)
        particles[i].integrate(dt);

    last_tick = current_time;
}

void Simulation::draw() {
    for (int i = 0; i < particles.size(); ++i)
        particles[i].draw();
}

void Simulation::addParticle(const Vector2 &pos) {
    particles.emplace_back(pos);
}
