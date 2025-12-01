//
// Created by Sebastian on 21/11/2025.
//
#ifndef SPARKLEEMITTER_H
#define SPARKLEEMITTER_H

#include "Particles/ParticleEmitter.h"

class SparkleEmitter : public ParticleEmitter {
public:
    explicit SparkleEmitter(const Vector2 &position)
        : ParticleEmitter(position, {1.0, 1.0, 0.0}) {
        lifetime_min = 0.05f;
        lifetime_max = 0.3f;
        angle_min = -1.0f;
        angle_max = 1.0f;
        speed_min = 0.2f;
        speed_max = 1.0f;
        spawn_gap = 0.1f;
    }
};

#endif // SPARKLEEMITTER_H
