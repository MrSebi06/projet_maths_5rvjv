//
// Created by mihne on 05/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLESYSTEM_H
#define PROJET_MATHS_5RVJV_PARTICLESYSTEM_H

#include <vector>

#include "Particle.h"


class ParticleSystem {
    struct ParticleInstance {
        Vector2 position;
        Vector3 color;
    };

    std::vector<Particle> particles;
    mutable std::vector<ParticleInstance> instanceData;

    GLuint VAO{}, VBO{}, EBO{};
    GLuint instanceVBO{};
    GLsizei indexCount{};

    static constexpr int MAX_PARTICLES = 10000;

    void setup_geometry();
    void setup_instance_buffer();

public:
    ParticleSystem(
    ) {
        setup_geometry();
        setup_instance_buffer();
    }

    void update(float dt);
    void draw() const;
    void emit();

    void add_force(const Vector2 &force);
};


#endif //PROJET_MATHS_5RVJV_PARTICLESYSTEM_H
