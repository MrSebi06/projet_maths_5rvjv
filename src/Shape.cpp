#include "Shape.h"

CircleShape::~CircleShape() noexcept = default;
ShapeType CircleShape::GetType() const { return CIRCLE; }
float CircleShape::getMomentOfInertia() const { return radius * radius / 2; }

ShapeType PolygonShape::GetType() const { return POLYGON; }
float PolygonShape::getMomentOfInertia() const { return 0.0f; }

std::vector<Vector2> PolygonShape::getTranslatedVertices(const Vector2 &translation) const
{
    std::vector<Vector2> res = vertices;
    for (auto& re : res)
        re += translation;
    return res;
}

BoxShape::BoxShape(float width, float height)
{
    vertices = std::vector<Vector2>(4);
    // Generate four corners
    vertices[0] = Vector2(-width / 2, height / 2);
    vertices[1] = Vector2(width / 2, height / 2);
    vertices[2] = Vector2(width / 2, -height / 2);
    vertices[3] = Vector2(-width / 2, -height / 2);

    broadRadius = vertices[0].magnitude();
}
ShapeType BoxShape::GetType() const { return POLYGON; }
float BoxShape::getMomentOfInertia() const { return (width * width + height * height) / 12; }
