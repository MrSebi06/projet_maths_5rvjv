//
// Created by Sebastian on 21/11/2025.
//

#include "Particles/ParticleEmitter.h"

#include "Engine.h"
#include "Random.h"

Vector2 ParticleEmitter::calculate_initial_velocity() const {
    const auto angle_dist = Random::float_dist(angle_min, angle_max);
    const auto speed_dist = Random::float_dist(speed_min, speed_max);

    return {
        Random::get_float(speed_dist) * Random::get_float(angle_dist),
        Random::get_float(speed_dist) * Random::get_float(angle_dist)
    };
}

float ParticleEmitter::calculate_lifetime() const {
    if (lifetime_min == lifetime_max) return lifetime_min;
    return Random::get_float(Random::float_dist(lifetime_min, lifetime_max));
}

void ParticleEmitter::play_for(const float seconds, const bool destroy_after_) {
    is_playing = true;
    destroy_after = destroy_after_;
    timed = true;
    timer = seconds;
}

void ParticleEmitter::update(const float dt) {
    if (!is_playing) return;

    if (timed) {
        timer -= dt;
        if (timer <= 0.0f) {
            if (destroy_after) {
                Engine::particles.mark_emitter_for_deletion(this);
                return;
            }
            is_playing = false;
            return;
        }
    }

    last_spawn += dt;
    if (last_spawn < spawn_gap) return;

    Engine::particles.emit(position, calculate_lifetime(), calculate_initial_velocity());
    last_spawn = 0.0f;
}
