//
// Created by Sacha TOUTUT on 02/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_COLLISIONDETECTION_H
#define PROJET_MATHS_5RVJV_COLLISIONDETECTION_H

#include "Rigidbody.h"

namespace CollisionDetection {
    struct CollisionInfo {
        Rigidbody2D *a;
        Rigidbody2D *b;
        Vector2 start, end;

        Vector2 normal;
        float depth;
    };

    inline bool isCollidingCircleCircle(Rigidbody2D *a, Rigidbody2D *b, CollisionInfo &info) {
        const auto *aCircleShape = dynamic_cast<CircleShape *>(a->shape);
        const auto bCircleShape = dynamic_cast<CircleShape *>(b->shape);

        const Vector2 aPos = a->transform->getPosition();
        const Vector2 bPos = b->transform->getPosition();

        const Vector2 ab = bPos - aPos;
        const float abMag = ab.magnitude();

        const float radiusSum = aCircleShape->radius + bCircleShape->radius;
        bool isColliding = abMag * abMag <= radiusSum * radiusSum;

        if (!isColliding) return false;
        info.a = a;
        info.b = b;

        info.normal = ab.normalized();
        info.start = bPos - info.normal * bCircleShape->radius;
        info.end = aPos + info.normal * aCircleShape->radius;
        info.depth = (info.end - info.start).magnitude();

        return true;
    }

    inline bool isColliding(Rigidbody2D *a, Rigidbody2D *b, CollisionInfo &info) {
        if (a->mass == 0 && b->mass == 0) return false;
        if ((b->transform->getPosition()-a->transform->getPosition()).magnitude() > a->shape->broadRadius + b->shape->broadRadius) {
            return false;
        }
        ShapeType aType = a->shape->GetType();
        ShapeType bType = b->shape->GetType();
        if (aType == CIRCLE && bType == CIRCLE)
            return isCollidingCircleCircle(a, b, info);

        // Default failsafe for unimplemented collisions
        return false;
    }

    inline void ResolveCollision(CollisionInfo &info) {
        Rigidbody2D *a = info.a;
        Rigidbody2D *b = info.b;

        // Penetration algorithm (Moves the objects on each other's bounds)
        float d = info.depth / (a->invMass + b->invMass);
        float da = d * a->invMass;
        float db = d * b->invMass;

        a->transform->addPosition(info.normal * -da);
        b->transform->addPosition(info.normal * db);

        // Impulse algorithm (Changes their velocities to move away)
        float elasticity = std::min(a->restitution, b->restitution);
        Vector2 velDiff = a->velocity - b->velocity;

        float impulseMag = -(1 + elasticity) * velDiff.dot(info.normal) / (a->invMass + b->invMass);
        Vector2 impulseDir = info.normal;

        Vector2 impulse = impulseDir * impulseMag;
        a->impulse(impulse);
        b->impulse(impulse * -1);
    }
}

#endif //PROJET_MATHS_5RVJV_COLLISIONDETECTION_H
