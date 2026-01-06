#include "Physics/CollisionShape.h"

#include "Mesh/Circle/Circle.h"
#include "Mesh/Polygon/Rect.h"
#include "Mesh/Polygon/Square.h"

BoxCollisionShape::BoxCollisionShape(const float width, const float height) {
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

ShapeType BoxCollisionShape::get_type() const { return POLYGON; }
float BoxCollisionShape::get_moment_of_inertia() const { return (width * width + height * height) / 12; }

std::shared_ptr<Mesh> BoxCollisionShape::to_mesh() const {
    if (width == height) {
        return std::make_shared<SquareMesh>(width);
    }
    return std::make_shared<RectMesh>(width, height);
}
