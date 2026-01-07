//
// Created by Sebastian on 21/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLEEMITTER_H
#define PROJET_MATHS_5RVJV_PARTICLEEMITTER_H

#include "Emitter.h"
#include "Engine.h"
#include "Vector/Vector2.h"
#include "Vector/Vector3.h"


class ParticleEmitter : public Emitter {
    Vector3 color;

protected:
    ParticleEmitter(const Vector2 &position, const Vector3 &color)
        : color(color) {
        this->position = position;
        Engine::particles.register_emitter(this);
    }

public:
    void update(float dt) override;
};


#endif //PROJET_MATHS_5RVJV_PARTICLEEMITTER_H
