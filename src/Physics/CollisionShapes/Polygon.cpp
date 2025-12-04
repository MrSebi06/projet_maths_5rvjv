//
// Created by mihne on 04/12/2025.
//

#include "Mesh/Circle/Circle.h"
#include "Physics/CollisionShape.h"

PolygonCollisionShape::PolygonCollisionShape(const std::vector<Vector2> &vertices) : vertices(vertices) {
    float maxDist = 0;
    for (const auto &vertice: vertices) {
        const float dist = vertice.magnitude();
        if (dist > maxDist) {
            maxDist = dist;
        }
    }
    broadRadius = maxDist;
}

ShapeType PolygonCollisionShape::get_type() const { return POLYGON; }

float PolygonCollisionShape::get_moment_of_inertia() const { return 0.0f; }

std::vector<Vector2> PolygonCollisionShape::getTranslatedVertices(const Vector2 &translation,
                                                                  const float &rotation) const {
    std::vector<Vector2> res = vertices;
    for (auto &re: res) {
        const Vector2 initialPoint = re;
        re.x = initialPoint.x * cosf(rotation) - initialPoint.y * sinf(rotation);
        re.y = initialPoint.y * cosf(rotation) + initialPoint.x * sinf(rotation);
        re += translation;
    }
    return res;
}

std::shared_ptr<Mesh> PolygonCollisionShape::to_mesh() const {
    throw std::runtime_error("Can't create meshes from PolygonCollisionShape yet");
}
