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

    inline float minSeparation(const std::vector<Vector2>& aVertices, const std::vector<Vector2>& bVertices, Vector2& axis, Vector2& point)
    {
        float separation = std::numeric_limits<float>::lowest();
        auto aPolyShapeSize = aVertices.size();
        auto bPolyShapeSize = bVertices.size();
        for (int i = 0; i < aPolyShapeSize; ++i)
        {
            // va <=> Vertex A
            Vector2 va = aVertices[i];
            Vector2 edge = aVertices[(i + 1) % aPolyShapeSize] - va;
            Vector2 normal = edge.perpendicular();

            float minSep = std::numeric_limits<float>::max();
            Vector2 minVertex;
            for (int j = 0; j < bPolyShapeSize; ++j)
            {
                auto vb = bVertices[j];

                float proj = (vb - va).dot(normal);
                if (proj < minSep)
                {
                    minSep = proj;
                    minVertex = vb;
                }
            }

            if (minSep > separation) {
                separation = minSep;
                axis = edge;
                point = minVertex;
            }
        }

        return separation;
    }

    inline bool isCollidingPolygonPolygon(Rigidbody2D *a, Rigidbody2D *b, CollisionInfo &info)
    {
        PolygonShape* aPolyShape = (PolygonShape*) a->shape;
        PolygonShape* bPolyShape = (PolygonShape*) b->shape;

        auto aTranslatedVertices = aPolyShape->getTranslatedVertices(a->transform->getPosition());
        auto bTranslatedVertices = bPolyShape->getTranslatedVertices(b->transform->getPosition());

        // Cut algorithm short for time if not needed
        Vector2 aAxis, aPoint;
        auto abSeparation = minSeparation(aTranslatedVertices, bTranslatedVertices, aAxis, aPoint);
        if (abSeparation > 0)
            return false;

        Vector2 bAxis, bPoint;
        auto baSeparation = minSeparation(bTranslatedVertices, aTranslatedVertices, bAxis, bPoint);
        if (baSeparation > 0)
            return false;

        info.a = a;
        info.b = b;

        if (abSeparation > baSeparation)
        {
            info.depth = -abSeparation;
            info.normal = aAxis.perpendicular();
            info.start = aPoint;
            info.end = aPoint + info.normal * info.depth;
        } else {
            info.depth = -baSeparation;
            info.normal = bAxis.perpendicular() * -1;
            info.start = bPoint - info.normal * info.depth;
            info.end = bPoint;
        }

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

        if (aType == POLYGON && bType == POLYGON)
            return isCollidingPolygonPolygon(a, b, info);

        // Default failsafe for unimplemented collisions
        return false;
    }

    inline void ResolveCollision(const CollisionInfo &info) {
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
