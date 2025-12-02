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

    inline float minSeparation(const std::vector<Vector2> &aVertices, const std::vector<Vector2> &bVertices,
                               Vector2 &axis, Vector2 &point) {
        float separation = std::numeric_limits<float>::lowest();
        auto aPolyShapeSize = aVertices.size();
        auto bPolyShapeSize = bVertices.size();
        for (int i = 0; i < aPolyShapeSize; ++i) {
            // va <=> Vertex A
            Vector2 va = aVertices[i];
            Vector2 edge = aVertices[(i + 1) % aPolyShapeSize] - va;
            Vector2 normal = edge.perpendicular();

            float minSep = std::numeric_limits<float>::max();
            Vector2 minVertex;
            for (int j = 0; j < bPolyShapeSize; ++j) {
                auto vb = bVertices[j];

                float proj = (vb - va).dot(normal);
                if (proj < minSep) {
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

    inline bool is_colliding_circle_circle(Rigidbody2D *a, Rigidbody2D *b, CollisionInfo &info) {
        const auto aCircleShape = dynamic_cast<CircleShape *>(a->shape);
        const auto bCircleShape = dynamic_cast<CircleShape *>(b->shape);

        const Vector2 aPos = a->transform->getPosition();
        const Vector2 bPos = b->transform->getPosition();

        const Vector2 ab = bPos - aPos;
        const float radiusSum = aCircleShape->radius + bCircleShape->radius;
        if (!(ab.magnitude_squared() <= radiusSum * radiusSum)) return false;

        info.a = a;
        info.b = b;

        info.normal = ab.normalized();
        info.start = bPos - info.normal * bCircleShape->radius;
        info.end = aPos + info.normal * aCircleShape->radius;
        info.depth = (info.end - info.start).magnitude();

        return true;
    }

    inline bool isCollidingPolygonPolygon(Rigidbody2D *a, Rigidbody2D *b, CollisionInfo &info) {
        PolygonShape *aPolyShape = (PolygonShape *) a->shape;
        PolygonShape *bPolyShape = (PolygonShape *) b->shape;

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

        if (abSeparation > baSeparation) {
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

    inline bool is_colliding(Rigidbody2D *a, Rigidbody2D *b, CollisionInfo &info) {
        const ShapeType aType = a->shape->GetType();
        const ShapeType bType = b->shape->GetType();
        if (aType == CIRCLE && bType == CIRCLE)
            return is_colliding_circle_circle(a, b, info);

        if (aType == POLYGON && bType == POLYGON)
            return isCollidingPolygonPolygon(a, b, info);

        // Default failsafe for unimplemented collisions
        return false;
    }


    inline void resolve_collision(const CollisionInfo &info) {
        Rigidbody2D *a = info.a;
        Rigidbody2D *b = info.b;

        // Penetration algorithm (Moves the objects on each other's bounds)
        const float d = info.depth / (a->invMass + b->invMass);
        const float da = d * a->invMass;
        const float db = d * b->invMass;

        a->transform->addPosition(info.normal * -da);
        b->transform->addPosition(info.normal * db);

        // Impulse algorithm (Changes their velocities to move away)
        const Vector2 ra = info.end - a->transform->getPosition();
        const Vector2 rb = info.start - b->transform->getPosition();

        const Vector2 va = a->velocity + Vector2(-(a->angularVelocity) * ra.getY(), a->angularVelocity * ra.getX());
        const Vector2 vb = b->velocity + Vector2(-(b->angularVelocity) * rb.getY(), b->angularVelocity * rb.getX());

        const Vector2 vrel = va - vb;
        const float elasticity = -(1 + std::min(a->restitution, b->restitution));
        const float sum_inv_masses = a->invMass + b->invMass;

        const float vrel_dot_normal = vrel.dot(info.normal);
        const float impulseMagN = elasticity * vrel_dot_normal /
                                  (sum_inv_masses
                                   + ra.cross(info.normal) * ra.cross(info.normal) * a->invI
                                   + rb.cross(info.normal) * rb.cross(info.normal) * b->invI);
        const Vector2 impulseN = info.normal * impulseMagN;

        const Vector2 tangent = info.normal.perpendicular();
        const float vrel_dot_tangent = vrel.dot(tangent);
        const float friction = std::min(a->friction, b->friction);
        const float impulseMagT = friction * elasticity * vrel_dot_tangent /
                                  (sum_inv_masses
                                   + ra.cross(tangent) * ra.cross(tangent) * a->invI
                                   + rb.cross(tangent) * rb.cross(tangent) * b->invI);
        const Vector2 impulseT = tangent * impulseMagT;

        const Vector2 impulse = impulseN + impulseT;

        a->impulse(impulse, ra);
        b->impulse(impulse * -1, rb);
    }
}

#endif //PROJET_MATHS_5RVJV_COLLISIONDETECTION_H
