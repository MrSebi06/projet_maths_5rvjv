//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLE_H
#define PROJET_MATHS_5RVJV_PARTICLE_H

#include "Vector2.h"

class Particle {
    Vector2 sumForces;

public:
    float mass;

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    void draw();
    void resetForces();
    void addForce(const Vector2& force);

    void integrate(const float& dt);
};


#endif //PROJET_MATHS_5RVJV_PARTICLE_H
