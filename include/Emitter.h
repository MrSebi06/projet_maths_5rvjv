//
// Created by mihne on 07/01/2026.
//

#ifndef PROJET_MATHS_5RVJV_EMITTER_H
#define PROJET_MATHS_5RVJV_EMITTER_H
#include "Vector/Vector2.h"


class Emitter {
protected:
    bool is_playing = false;
    bool timed = false;
    bool destroy_after = false;
    float timer = 0.0f;

    float last_spawn = 0.0f;

    Vector2 position;

    Vector2 calculate_initial_velocity() const;
    float calculate_lifetime() const;

public:
    Vector2 base_initial_velocity = Vector2(0.0f, 0.0f);
    float angle_min = 0.0f;
    float angle_max = 0.0f;
    float speed_min = 0.0f;
    float speed_max = 0.0f;

    float lifetime_min = 0.0f;
    float lifetime_max = 0.0f;

    float spawn_gap = 0.0f;

    void start();
    void stop();
    void play_for(float seconds, bool destroy_after_ = false);
    virtual void update(float dt) = 0;

    void set_position(const Vector2 &position);

    virtual ~Emitter() = default;
};


#endif //PROJET_MATHS_5RVJV_EMITTER_H
