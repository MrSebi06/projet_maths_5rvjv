//
// Created by mihne on 11/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_ENGINE_H
#define PROJET_MATHS_5RVJV_ENGINE_H

#include "GameObject.h"
#include "Physics/PhysicsSystem.h"
#include "Particles/ParticleSystem.h"

namespace Engine {
    inline PhysicsSystem physics;
    inline ParticleSystem particles;
    inline std::vector<std::unique_ptr<GameObject> > game_objects;
    inline std::vector<MeshRenderer *> debug_renderers;

    inline GLuint debug_shader = -1;

    inline void init(const GLuint particle_shader, const GLuint debug_shader_ = -1) {
        particles.init(particle_shader);
        debug_shader = debug_shader_;
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
        for (const auto &renderer: debug_renderers) {
            renderer->draw();
        }
    }

    inline GameObject *create_game_object(const Vector2 &pos = Vector2{0.0f, 0.0f}, const float rot = 0.0f) {
        game_objects.push_back(std::make_unique<GameObject>(pos, rot));
        return game_objects.back().get();
    }

    inline void clear_game_objects(
    ) {
        game_objects.clear();
        physics.clear_bodies();
        debug_renderers.clear();
    }

    inline void register_debug_renderer(MeshRenderer *renderer) {
        debug_renderers.push_back(renderer);
    }
}

#endif //PROJET_MATHS_5RVJV_ENGINE_H
