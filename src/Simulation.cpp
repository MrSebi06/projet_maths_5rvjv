//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <Simulation.h>

#define GRAVITY Vector2(0, -9.81f)

void Simulation::update() {
    // Calculate delta time using system clock
    const auto current_time = std::chrono::high_resolution_clock::now();
    const auto elapsed = current_time - last_tick;
    const auto elapsed_ms = duration_cast<std::chrono::microseconds>(elapsed);
    const float dt = elapsed_ms.count() / 1000000.0f;

    for (const auto &particle_system: particle_systems) {
        particle_system->add_force(wind);
        particle_system->add_force(GRAVITY);
        particle_system->update(dt);
    }

    last_tick = current_time;
}

void Simulation::draw() const {
    for (const auto &particle_system: particle_systems)
        particle_system->draw();
}

