//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include <Physics/PhysicsSystem.h>

#include <Engine.h>
#include <Physics/CollisionDetection.h>
#include <algorithm>

#define GRAVITY Vector2(0, -9.81f)

void PhysicsSystem::update(const float dt) const {
    Engine::particles.add_force(wind);
    Engine::particles.add_force(GRAVITY);

    for (const auto body: bodies) {
        body->add_force(wind);
        body->add_force(GRAVITY * body->mass);

        body->integrate(dt);
    }

    // After the basic physics update, resolve collisions
    for (int i = 0; i < bodies.size(); ++i) {
        Rigidbody2D *currentBody = bodies[i];

        for (int j = i + 1; j < bodies.size(); ++j) {
            CollisionDetection::CollisionInfo info;
            if (CollisionDetection::is_colliding(currentBody, i, bodies[j], j, info))
                CollisionDetection::resolve_collision(info, this);
        }
    }
}

void PhysicsSystem::addPositionSticky(std::vector<int> *excludedBodies, int bodyIndex, const Vector2 &positionAdded) const {
    if (bodies[bodyIndex]->mass == 0)
        return;
    if (std::ranges::find(*excludedBodies, bodyIndex) == excludedBodies->end())
        excludedBodies->push_back(bodyIndex);
    std::vector<int> collidingBodies = std::vector<int>();
    for (int i = 0; i < bodies.size(); ++i) {
        if (i == bodyIndex)
            continue;
        if (std::ranges::find(*excludedBodies, i) != excludedBodies->end())
            continue;
        CollisionDetection::CollisionInfo info;
        if (
            ((bodies[i]->transform->getPosition() - bodies[bodyIndex]->transform->getPosition()).magnitude() <= bodies[bodyIndex]->shape->broadRadius ||
             positionAdded.dot(bodies[i]->transform->getPosition() - bodies[bodyIndex]->transform->getPosition()) < -0.7)
            &&
            CollisionDetection::is_colliding(bodies[bodyIndex], bodyIndex, bodies[i], i, info)) {
            excludedBodies->push_back(i);
            collidingBodies.push_back(i);
        }
    }
    for (int colliding_body: collidingBodies)
        addPositionSticky(excludedBodies, colliding_body, positionAdded);
    bodies[bodyIndex]->transform->addPosition(positionAdded);
}

void PhysicsSystem::register_rigid_body(Rigidbody2D *body) {
    bodies.push_back(body);
}

void PhysicsSystem::unregister_rigid_body(Rigidbody2D *body) {
    bodies.erase(std::ranges::remove(bodies, body).begin(), bodies.end());
}

void PhysicsSystem::clear_bodies() {
    bodies.clear();
}

void PhysicsSystem::add_wind(const Vector2 &wind_) {
    wind += wind_;
}
