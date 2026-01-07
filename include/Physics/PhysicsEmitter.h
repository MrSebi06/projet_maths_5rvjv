//
// Created by mihne on 07/01/2026.
//

#ifndef PROJET_MATHS_5RVJV_PHYSICSEMITTER_H
#define PROJET_MATHS_5RVJV_PHYSICSEMITTER_H
#include "Emitter.h"
#include "Engine.h"
#include "Physics/CollisionShape.h"


class PhysicsEmitter final : public Emitter {
    const float mass;
    const float restitution;
    const float friction;
    CollisionShape *shape;
    const bool debug;
    const bool is_liquid;

    const GLuint base_shader_program;

public:
    PhysicsEmitter(const Vector2 &position_, const GLuint base_shader_program, const float mass,
                   const float restitution,
                   const float friction,
                   CollisionShape *shape, const bool debug,
                   const bool is_liquid) : mass(mass),
                                           restitution(restitution),
                                           friction(friction),
                                           shape(shape),
                                           debug(debug),
                                           is_liquid(is_liquid),
                                           base_shader_program(base_shader_program) {
        Engine::physics.register_emitter(this);

        position = position_;
        spawn_gap = 0.1f;

        lifetime_min = 1.0f;
        lifetime_max = 2.0f;
        angle_min = -0.2f;
        angle_max = 0.2f;
        speed_min = 0.2f;
        speed_max = 1.0f;
    }

    void update(float dt) override;
};


#endif //PROJET_MATHS_5RVJV_PHYSICSEMITTER_H
