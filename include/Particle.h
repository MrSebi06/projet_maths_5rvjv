//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLE_H
#define PROJET_MATHS_5RVJV_PARTICLE_H

#include "Vector/Vector2.h"
#include "Mesh/Circle/Circle.h"

struct Particle {
    Vector2 sumForces;

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Vector3 color;

    explicit Particle(const Vector2 &pos, const Vector3 &color, const float mass = 1.0f)
        : mass(mass),
          position(pos),
          color(color),
          velocity(),
          acceleration() {}

    float mass;

    void resetForces();
    void addForce(const Vector2 &force);

    void integrate(const float &dt);
};


#endif //PROJET_MATHS_5RVJV_PARTICLE_H
