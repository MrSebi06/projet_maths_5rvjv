#include "../../include/Physics/CollisionShape.h"

CircleCollisionShape::~CircleCollisionShape() noexcept = default;
ShapeType CircleCollisionShape::GetType() const { return CIRCLE; }
float CircleCollisionShape::getMomentOfInertia() const { return radius * radius / 2; }

ShapeType PolygonCollisionShape::GetType() const { return POLYGON; }
float PolygonCollisionShape::getMomentOfInertia() const { return 0.0f; }

std::vector<Vector2> PolygonCollisionShape::getTranslatedVertices(const Vector2 &translation) const
{
    std::vector<Vector2> res = vertices;
    for (auto& re : res)
        re += translation;
    return res;
}

BoxCollisionShape::BoxCollisionShape(float width, float height)
{
    this->width = width;
    this->height = height;
    vertices = std::vector<Vector2>(4);
    // Generate four corners
    vertices[0] = Vector2(-width / 2, height / 2);
    vertices[1] = Vector2(width / 2, height / 2);
    vertices[2] = Vector2(width / 2, -height / 2);
    vertices[3] = Vector2(-width / 2, -height / 2);

    broadRadius = vertices[0].magnitude();
}
ShapeType BoxCollisionShape::GetType() const { return POLYGON; }
float BoxCollisionShape::getMomentOfInertia() const { return (width * width + height * height) / 12; }
