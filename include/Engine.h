//
// Created by mihne on 11/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_ENGINE_H
#define PROJET_MATHS_5RVJV_ENGINE_H

#include "PhysicsSystem.h"
#include "ParticleSystem.h"


namespace Engine {
    inline PhysicsSystem physics;
    inline ParticleSystem particles;

    inline void init() {
        particles.init();
    }

    inline void update(const float dt) {
        physics.update(dt);
        particles.update(dt);
    }

    inline void draw() {
        particles.draw();
    }
}


#endif //PROJET_MATHS_5RVJV_ENGINE_H
