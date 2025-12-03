
#ifndef PROJET_MATHS_5RVJV_SHAPE_H
#define PROJET_MATHS_5RVJV_SHAPE_H

#include <vector>
#include "../Vector/Vector2.h"

enum ShapeType {
    CIRCLE,
    POLYGON,
    BOX
};

struct CollisionShape {
    float broadRadius = 0;
    virtual ~CollisionShape() = default;
    virtual ShapeType GetType() const = 0;
    virtual float getMomentOfInertia() const = 0;
};

struct CircleCollisionShape : public CollisionShape {
    float radius=0;

    explicit CircleCollisionShape(const float radius) : radius(radius) { broadRadius = radius; };
    virtual ~CircleCollisionShape();
    ShapeType GetType() const override;

    float getMomentOfInertia() const override;
};

struct PolygonCollisionShape : public CollisionShape {
    std::vector<Vector2> vertices;

    PolygonCollisionShape() = default;

    explicit PolygonCollisionShape(const std::vector<Vector2> &vertices) : vertices(vertices) {
        float maxDist = 0;
        for (auto vertice: vertices) {
            float dist = vertice.magnitude();
            if (dist > maxDist) {
                maxDist = dist;
            }
        }
        broadRadius = maxDist;
    };
    virtual ~PolygonCollisionShape() = default;
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
    std::vector<Vector2> getTranslatedVertices(const Vector2& translation, const float& rotation) const;
};

struct BoxCollisionShape : public PolygonCollisionShape {
    float width=0, height=0;
    BoxCollisionShape(float width, float height);
    virtual ~BoxCollisionShape() = default;
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
};

#endif //PROJET_MATHS_5RVJV_SHAPE_H
