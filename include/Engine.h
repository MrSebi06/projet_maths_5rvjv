//
// Created by mihne on 11/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_ENGINE_H
#define PROJET_MATHS_5RVJV_ENGINE_H

#include "GameObject.h"
#include "PhysicsSystem.h"
#include "Particles/ParticleSystem.h"


class MeshRenderer;

namespace Engine {
    inline PhysicsSystem physics;
    inline ParticleSystem particles;
    inline std::vector<std::unique_ptr<GameObject> > game_objects;

    inline void init(const GLuint particle_shader) {
        particles.init(particle_shader);
    }

    inline void update(const float dt) {
        physics.update(dt);
        particles.update(dt);
    }

    inline void draw() {
        particles.draw();
        for (const auto &go: game_objects) {
            go->draw();
        }
    }

    inline GameObject *create_game_object(const Vector2 &pos = Vector2{0.0f, 0.0f}) {
        game_objects.push_back(std::make_unique<GameObject>(pos));
        return game_objects.back().get();
    }
}


#endif //PROJET_MATHS_5RVJV_ENGINE_H
