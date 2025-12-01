#include "Shape.h"

CircleShape::~CircleShape() noexcept = default;
ShapeType CircleShape::GetType() const { return CIRCLE; }
float CircleShape::getMomentOfInertia() const { return radius * radius / 2; }

ShapeType PolygonShape::GetType() const { return POLYGON; }
float PolygonShape::getMomentOfInertia() const { return 0.0f; }

BoxShape::BoxShape(float width, float height)
{
    vertices = std::vector<Vector2>(4);
    // Generate four corners
    vertices[0] = Vector2(-width / 2, -height / 2);
    vertices[0] = Vector2(width / 2, -height / 2);
    vertices[0] = Vector2(width / 2, height / 2);
    vertices[0] = Vector2(-width / 2, height / 2);
}
ShapeType BoxShape::GetType() const { return BOX; }
float BoxShape::getMomentOfInertia() const { return (width * width + height * height) / 12; }
