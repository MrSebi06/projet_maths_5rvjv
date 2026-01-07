#include "Physics/LiquidBody.h"
#include <cmath>
#include <numbers>

std::vector<LiquidBody *> LiquidBody::liquidBodies;

const float LiquidBody::NEIGHBORHOOD_RADIUS = 0.2f;
const float LiquidBody::REST_DENSITY = 0.1;

// Poly6 Kernel with 2D constants
float LiquidBody::density_kernel(float r, float h) {
    float hr = h * h - r * r;
    float pi_h_8 = std::numbers::pi_v<float> * powf(h, 8.0f);
    return (4.0f / pi_h_8) * powf(hr, 3);
}

// Spiky Kernel - Gradient version, apparently
float LiquidBody::pressure_kernel(float r, float h) {
    float hr = powf(h - r, 2);
    float pi_h_5 = std::numbers::pi_v<float> * powf(h, 5);
    return (-30.0f / pi_h_5) * hr;
}

float LiquidBody::viscosity_kernel(float r, float h) {
    float hr = h - r;
    float pi_h_5 = std::numbers::pi_v<float> * powf(h, 5);
    return (20 / pi_h_5) * hr;
}

LiquidBody::LiquidBody(Transform *transform, const float &mass, const float &restitution, float friction,
                       CollisionShape *shape, bool debug) : Rigidbody2D(transform, mass, restitution, friction, shape,
                                                                        debug) {
    liquidBodies.push_back(this);
}

std::vector<LiquidBody *> LiquidBody::get_neighbors() {
    auto neighbors = std::vector<LiquidBody *>();
    for (LiquidBody *otherBody: liquidBodies) {
        if (otherBody == this) continue;

        if ((otherBody->transform->getPosition() - transform->getPosition()).magnitude() <= NEIGHBORHOOD_RADIUS)
            neighbors.push_back(otherBody);
    }

    return neighbors;
}

void LiquidBody::integrate(float dt) {
    Vector2 position = transform->getPosition();

    auto neighbors = get_neighbors();

    // The objective of fluid simulation is to try and reach REST_DENSITY
    // So first, calculate current density
    density = 0.0f;
    for (auto neighbor: neighbors) {
        auto toNeighbor = neighbor->transform->getPosition() - position;
        auto r = toNeighbor.magnitude();

        density += neighbor->mass * density_kernel(r, NEIGHBORHOOD_RADIUS);
    }
    // Count yourself!
    density += mass * density_kernel(0, NEIGHBORHOOD_RADIUS);

    // Difference in density from the preferred value (REST_DENSITY) encourages movement
    // Note: 0.5 is a magic value which we should parameterize...
    pressure = 0.1f * (density - REST_DENSITY);
    pressure = std::max(0.0f, pressure);

    // Once pressure is calculated, we iterate through neighbors again to apply their forces
    for (auto neighbor: neighbors) {
        auto toNeighbor = neighbor->transform->getPosition() - position;
        if (neighbor->density == 0 || (toNeighbor.x == 0 && toNeighbor.y == 0))
            continue;
        auto r = toNeighbor.magnitude();

        // Add Pressure force
        auto pressure_strength = -neighbor->mass * (pressure + neighbor->pressure) / (2 * neighbor->density) *
                                 pressure_kernel(r, NEIGHBORHOOD_RADIUS);
        auto pressure_force = toNeighbor.normalized() * pressure_strength;
        add_force(pressure_force * -1);
        neighbor->add_force(pressure_force);
    }

    Rigidbody2D::integrate(dt);
}
