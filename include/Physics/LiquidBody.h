//
// Created by Sacha TOUTUT on 06/01/2026.
//

#ifndef PROJET_MATHS_5RVJV_LIQUIDBODY_H
#define PROJET_MATHS_5RVJV_LIQUIDBODY_H

#include "Rigidbody.h"
#include <vector>
#include <Transform.h>

class LiquidBody : public Rigidbody2D
{
private:
    static std::vector<LiquidBody*> liquidBodies;
    static const float NEIGHBORHOOD_RADIUS;
    static const float VISCOSITY;
    static const float REST_DENSITY;

    std::vector<LiquidBody*> get_neighbors();

    // Kernels
    static float density_kernel(float r, float h);
    static float pressure_kernel(float r, float h);
    static float viscosity_kernel(float r, float h);

public:
    float density, pressure;

    LiquidBody(Transform *transform, const float &mass, const float &restitution, float friction,
            CollisionShape *shape, bool debug = false);

    void integrate(float dt) override;
};

#endif //PROJET_MATHS_5RVJV_LIQUIDBODY_H
