//
// Created by mihne on 11/11/2025.
//

#include "Engine.h"

void Engine::update(const float dt) const {
    physics_system->update(dt);
    particle_system->update(dt);
}

void Engine::draw() const {
    particle_system->draw();
}

void Engine::emit_particle() const {
    particle_system->emit();
}

void Engine::add_wind(const Vector2 &wind) const {
    physics_system->add_wind(wind);
}
