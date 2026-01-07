//
// Created by mihne on 07/01/2026.
//

#include "../../include/Physics/PhysicsEmitter.h"

#include "Engine.h"

void PhysicsEmitter::update(const float dt) {
    if (!is_playing) return;

    if (timed) {
        timer -= dt;
        if (timer <= 0.0f) {
            if (destroy_after) {
                return;
            }
            is_playing = false;
            return;
        }
    }

    last_spawn += dt;
    if (last_spawn < spawn_gap) return;

    const auto mesh = std::make_shared<CircleMesh>(0.05f, 20);
    const auto game_object = Engine::create_game_object(position);
    game_object->add_renderer(mesh, base_shader_program, Vector3(0.0f, 0.0f, 1.0f));
    game_object->add_liquidbody(mass, restitution, friction, shape);

    last_spawn = 0.0f;
}
