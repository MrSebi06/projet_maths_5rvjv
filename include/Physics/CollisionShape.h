
#ifndef PROJET_MATHS_5RVJV_SHAPE_H
#define PROJET_MATHS_5RVJV_SHAPE_H

#include <memory>
#include <vector>
#include "Vector/Vector2.h"
#include "Mesh/Mesh.h"

enum ShapeType {
    CIRCLE,
    POLYGON,
    BOX
};

struct CollisionShape {
    float broadRadius = 0;

    virtual ~CollisionShape() = default;

    virtual ShapeType get_type() const = 0;
    virtual float get_moment_of_inertia() const = 0;

    virtual std::shared_ptr<Mesh> to_mesh() const = 0;
};

struct CircleCollisionShape final : CollisionShape {
    float radius = 0;

    explicit CircleCollisionShape(const float radius) : radius(radius) { broadRadius = radius; };
    ~CircleCollisionShape() override = default;

    ShapeType get_type() const override;
    float get_moment_of_inertia() const override;

    std::shared_ptr<Mesh> to_mesh() const override;
};

struct PolygonCollisionShape : CollisionShape {
    std::vector<Vector2> vertices;

    PolygonCollisionShape() = default;

    explicit PolygonCollisionShape(const std::vector<Vector2> &vertices);
    ~PolygonCollisionShape() override = default;

    ShapeType get_type() const override;
    float get_moment_of_inertia() const override;

    std::shared_ptr<Mesh> to_mesh() const override;

    std::vector<Vector2> getTranslatedVertices(const Vector2 &translation, const float &rotation) const;
};

struct BoxCollisionShape final : PolygonCollisionShape {
    float width = 0, height = 0;

    BoxCollisionShape(float width, float height);
    ~BoxCollisionShape() override = default;

    ShapeType get_type() const override;
    float get_moment_of_inertia() const override;

    std::shared_ptr<Mesh> to_mesh() const override;
};

#endif //PROJET_MATHS_5RVJV_SHAPE_H
