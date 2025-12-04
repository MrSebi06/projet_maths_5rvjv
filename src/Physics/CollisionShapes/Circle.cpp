//
// Created by mihne on 04/12/2025.
//

#include "Mesh/Circle/Circle.h"
#include "Physics/CollisionShape.h"


ShapeType CircleCollisionShape::get_type() const { return CIRCLE; }

float CircleCollisionShape::get_moment_of_inertia() const { return radius * radius / 2; }

std::shared_ptr<Mesh> CircleCollisionShape::to_mesh() const {
    return std::make_shared<CircleMesh>(radius, 10);
}
