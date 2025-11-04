//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLE_H
#define PROJET_MATHS_5RVJV_PARTICLE_H

#include "Vector/Vector2.h"
#include "Mesh/Circle/Circle.h"

class Particle {
    Vector2 sumForces;

public:
    Mesh *mesh;

    explicit Particle(const Vector2 &pos, float mass = 1.0f)
        : mesh(new Circle(0.1f, 100)),
          mass(mass),
          position(pos),
          velocity(),
          acceleration() {
    }

    float mass;

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    void draw() const;

    void resetForces();

    void addForce(const Vector2 &force);

    void integrate(const float &dt);
};


#endif //PROJET_MATHS_5RVJV_PARTICLE_H
