//
// Created by mihne on 07/01/2026.
//

#include "../include/Emitter.h"

#include "Engine.h"
#include "Random.h"

Vector2 Emitter::calculate_initial_velocity() const {
    const auto angle_dist = Random::float_dist(angle_min, angle_max);
    const auto speed_dist = Random::float_dist(speed_min, speed_max);

    return {
        Random::get_float(speed_dist) * Random::get_float(angle_dist),
        Random::get_float(speed_dist) * Random::get_float(angle_dist)
    };
}

float Emitter::calculate_lifetime() const {
    if (lifetime_min == lifetime_max) return lifetime_min;
    return Random::get_float(Random::float_dist(lifetime_min, lifetime_max));
}

void Emitter::play_for(const float seconds, const bool destroy_after_) {
    is_playing = true;
    destroy_after = destroy_after_;
    timed = true;
    timer = seconds;
}

void Emitter::start() {
    is_playing = true;
    timed = false;
    destroy_after = false;
}

void Emitter::stop() {
    is_playing = false;
}

void Emitter::set_position(const Vector2 &position_) {
    position = position_;
}


