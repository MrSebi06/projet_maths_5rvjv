
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
    virtual ~Shape() = default;
    virtual ShapeType GetType() const = 0;
    virtual float getMomentOfInertia() const = 0;
    virtual float getBroadRadius() = 0;
};

struct CircleShape: public Shape {
    float radius;

    explicit CircleShape(const float radius) : radius(radius) {};
    virtual ~CircleShape();
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
    float getBroadRadius() override;
};

struct PolygonShape: public Shape {
    std::vector<Vector2> vertices;

    PolygonShape() = default;
    explicit PolygonShape(const std::vector<Vector2>& vertices) : vertices(vertices) {};
    virtual ~PolygonShape() = default;
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
    float getBroadRadius() override;
};

struct BoxShape: public PolygonShape {
    float width, height;
    BoxShape(float width, float height);
    virtual ~BoxShape() = default;
    ShapeType GetType() const override;
    float getMomentOfInertia() const override;
    float getBroadRadius() override;
};

#endif //PROJET_MATHS_5RVJV_SHAPE_H
