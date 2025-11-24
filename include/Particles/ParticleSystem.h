//
// Created by mihne on 05/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLESYSTEM_H
#define PROJET_MATHS_5RVJV_PARTICLESYSTEM_H

#include <Vector/Vector2.h>
#include <Vector/Vector3.h>

#include "Particle.h"
#include "ParticleEmitter.h"

class ParticleEmitter;

class ParticleSystem {
    struct ParticleInstance {
        Vector2 position;
        Vector3 color;
    };

    std::vector<ParticleEmitter *> emitters;

    std::vector<Particle> particles;
    mutable std::vector<ParticleInstance> instance_data;

    GLuint VAO{}, VBO{}, EBO{};
    GLuint instanceVBO{};
    GLsizei indexCount{};

    static constexpr int MAX_PARTICLES = 10000;

    void setup_geometry();
    void setup_instance_buffer();

public:
    void init();
    void update(float dt);
    void draw() const;

    void emit(const Vector2 &pos, float lifetime, const Vector2 &initial_velocity);
    void add_force(const Vector2 &force);

    void register_emitter(ParticleEmitter *emitter) {
        emitters.emplace_back(emitter);
    }

    void unregister_emitter(ParticleEmitter *emitter) {
        std::erase(emitters, emitter);
    }
};


#endif //PROJET_MATHS_5RVJV_PARTICLESYSTEM_H
