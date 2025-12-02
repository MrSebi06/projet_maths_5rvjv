
#ifndef PROJET_MATHS_5RVJV_SHAPE_H
#define PROJET_MATHS_5RVJV_SHAPE_H

#include <vector>
#include "Vector/Vector2.h"

enum ShapeType {
    CIRCLE,
    POLYGON,
    BOX
};

struct Shape {
    float broadRadius = 0;
    virtual ~Shape() = default;
    virtual ShapeType GetType() const = 0;
    virtual float getMomentOfInertia() const = 0;
};

struct CircleShape: public Shape {
    float radius;

    explicit CircleShape(const float radius) : radius(radius) {broadRadius = radius;};
    virtual ~CircleShape();
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
};

struct PolygonShape: public Shape {
    std::vector<Vector2> vertices;

    PolygonShape() = default;
    explicit PolygonShape(const std::vector<Vector2>& vertices) : vertices(vertices) {
        float maxDist = 0;
        for (auto vertice: vertices) {
            float dist = vertice.magnitude();
            if (dist>maxDist) {
                maxDist = dist;
            }
        }
        broadRadius = maxDist;
    };
    virtual ~PolygonShape() = default;
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
    std::vector<Vector2> getTranslatedVertices(const Vector2& translation) const;
};

struct BoxShape: public PolygonShape {
    float width, height;
    BoxShape(float width, float height);
    virtual ~BoxShape() = default;
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
};

#endif //PROJET_MATHS_5RVJV_SHAPE_H
