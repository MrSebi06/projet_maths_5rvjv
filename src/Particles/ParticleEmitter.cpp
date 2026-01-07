//
// Created by Sebastian on 21/11/2025.
//

#include "Particles/ParticleEmitter.h"

#include "Engine.h"
#include "Random.h"

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
