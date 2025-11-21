//
// Created by Sebastian on 21/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_PARTICLEEMITTER_H
#define PROJET_MATHS_5RVJV_PARTICLEEMITTER_H

#include "Vector/Vector2.h"
#include "Vector/Vector3.h"


class ParticleEmitter {
    bool is_playing = false;
    bool timed = false;
    bool destroy_after = false;
    float timer = 0.0f;

    Vector2 position;


    Vector3 color;

    Vector2 calculate_initial_velocity() const;
    float calculate_lifetime() const;

protected:
    ParticleEmitter(const Vector2 &position, const Vector3 &color)
        : position(position),
          color(color) {}

public:
    Vector2 base_initial_velocity = Vector2(0.0f, 0.0f);
    float angle_min = 0.0f;
    float angle_max = 0.0f;
    float speed_min = 0.0f;
    float speed_max = 0.0f;

    float lifetime_min = 0.0f;
    float lifetime_max = 0.0f;

    void start();
    void stop();
    void play_for(float seconds, bool destroy_after_ = false);
    void update(float dt);

    ~ParticleEmitter() = default;
};


#endif //PROJET_MATHS_5RVJV_PARTICLEEMITTER_H
