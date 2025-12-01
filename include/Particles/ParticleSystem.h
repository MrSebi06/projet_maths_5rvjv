//
// Created by mihne on 05/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLESYSTEM_H
#define PROJET_MATHS_5RVJV_PARTICLESYSTEM_H

#include <unordered_set>
#include <unordered_map>
#include <Vector/Vector2.h>
#include <Vector/Vector3.h>

#include "Particle.h"

class ParticleEmitter;

class ParticleSystem {
    struct ParticleInstance {
        Vector2 position;
        Vector3 color;
    };

    std::unordered_map<size_t, ParticleEmitter *> emitters;
    std::unordered_set<size_t> emitters_to_delete;

    std::vector<Particle> particles;
    mutable std::vector<ParticleInstance> instance_data;

    GLuint shader_program = -1;
    GLuint VAO{}, VBO{}, EBO{};
    GLuint instanceVBO{};
    GLsizei indexCount{};

    static constexpr int MAX_PARTICLES = 100000;

    void setup_geometry();
    void setup_instance_buffer();

public:
    void init(GLuint shader);
    void update(float dt);
    void draw() const;

    void emit(const Vector2 &pos, float lifetime, const Vector2 &initial_velocity);
    void add_force(const Vector2 &force);

    void register_emitter(ParticleEmitter *emitter);

    void mark_emitter_for_deletion(ParticleEmitter *emitter);
};


#endif //PROJET_MATHS_5RVJV_PARTICLESYSTEM_H
