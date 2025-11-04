//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <Simulation.h>
#include <iostream>

void Simulation::update() {
    // Calculate delta time using system clock
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed = current_time - last_tick;
    auto elapsed_ms = duration_cast<std::chrono::milliseconds>(elapsed);
    float dt = elapsed_ms.count() / 1000.0f;

    for (int i = 0; i < particles.size(); ++i) {
        particles[i].addForce(wind);
        particles[i].integrate(dt);
    }

    last_tick = current_time;
}

void Simulation::draw() {
    for (int i = 0; i < particles.size(); ++i)
        particles[i].draw();
}

void Simulation::addParticle(const Vector2 &pos) {
    particles.emplace_back(pos);
}
