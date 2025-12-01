//
// Created by mihne on 11/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_ENGINE_H
#define PROJET_MATHS_5RVJV_ENGINE_H

#include "GameObject.h"
#include "PhysicsSystem.h"
#include "Particles/ParticleSystem.h"



namespace CollisionDetection {
    struct CollisionInfo
    {
        Rigidbody2D* a;
        Rigidbody2D* b;
        Vector2 start, end;

        Vector2 normal;
        float depth;
    };

    inline bool isCollidingCircleCircle(Rigidbody2D* a, Rigidbody2D* b, CollisionInfo& info)
    {
        CircleShape* aCircleShape = (CircleShape*) a->shape;
        CircleShape* bCircleShape = (CircleShape*) b->shape;

        const Vector2 ab = b->position-a->position;
        const float abMag = ab.magnitude();

        const float radiusSum = aCircleShape->radius + bCircleShape->radius;
        bool isColliding = abMag * abMag <= radiusSum * radiusSum;

        if (!isColliding) return false;
        info.a = a;
        info.b = b;

        info.normal = ab.normalized();
        info.start = b->position - info.normal * bCircleShape->radius;
        info.end = a->position + info.normal* aCircleShape->radius;
        info.depth = (info.end - info.start).magnitude();

        return true;
    }

    inline bool isColliding(Rigidbody2D* a, Rigidbody2D* b, CollisionInfo& info)
    {
        ShapeType aType = a->shape->GetType();
        ShapeType bType = b->shape->GetType();
        if (aType == CIRCLE && bType == CIRCLE)
            return isCollidingCircleCircle(a, b, info);

        // Default failsafe for unimplemented collisions
        return false;
    }

    inline void ResolveCollision(CollisionInfo& info)
    {
        Rigidbody2D* a = info.a;
        Rigidbody2D* b = info.b;

        float d = info.depth / (a->invMass + b->invMass);
        float da = d * a->invMass;
        float db = d * b->invMass;

        a->position -= info.normal * da;
        b->position += info.normal * db;
    }
}

namespace Engine {
    inline PhysicsSystem physics;
    inline ParticleSystem particles;
    inline std::vector<std::unique_ptr<GameObject> > game_objects;

    inline void init(const GLuint particle_shader) {
        particles.init(particle_shader);
    }

    inline void update(const float dt) {
        physics.update(dt);
        particles.update(dt);

        for (int i = 0; i < objects.size(); ++i)
        {
            Rigidbody2D* body = objects[i];
            body->integrate(dt);

            for (int j = i+1; j < objects.size(); ++j)
            {
                CollisionDetection::CollisionInfo info;
                if (CollisionDetection::isColliding(body, objects[j], info))
                    CollisionDetection::ResolveCollision(info);
            }
        }
    }

    inline void draw() {
        particles.draw();
        for (const auto &go: game_objects) {
            go->draw();
        }
    }

    inline GameObject *create_game_object(const Vector2 &pos = Vector2{0.0f, 0.0f}) {
        game_objects.push_back(std::make_unique<GameObject>(pos));
        return game_objects.back().get();
    }
}

#endif //PROJET_MATHS_5RVJV_ENGINE_H
