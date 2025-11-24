//
// Created by Sebastian on 21/11/2025.
//
#ifndef LIQUIDSTREAMEMITTER_H
#define LIQUIDSTREAMEMITTER_H

#include "Engine.h"
#include "Particles/ParticleEmitter.h"

class LiquidStreamEmitter : public ParticleEmitter {
public:
    explicit LiquidStreamEmitter(const Vector2 &position)
        : ParticleEmitter(position, {1.0, 1.0, 0.0}) {
        lifetime_min = 1.0f;
        lifetime_max = 2.0f;
        angle_min = -0.3f;
        angle_max = 0.3f;
        speed_min = 0.2f;
        speed_max = 0.3f;
    }
};

#endif // LIQUIDSTREAMEMITTER_H
