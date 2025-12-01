//
// Created by mihne on 04/11/2025.
//

#ifndef PROJET_MATHS_5RVJV_CIRCLE_H
#define PROJET_MATHS_5RVJV_CIRCLE_H

#include <cmath>
#include <vector>

#include "helpers.h"
#include "Mesh/Mesh.h"
#include "Vector/Vector3.h"


class Circle : public Mesh {
public:
    float radius;
    unsigned int segments;

    explicit Circle(const float radius, const unsigned int segments) : radius(radius),
                                                                       segments(segments) {
        const double angle = 360.0 / segments;

        std::vector<Vector2> vertices;
        for (unsigned int i = 0; i < segments; i++) {
            const double currentAngle = angle * i;
            double x = radius * cos(deg2rad(currentAngle));
            double y = radius * sin(deg2rad(currentAngle));

            vertices.emplace_back(x, y);
        }

        std::vector<GLuint> indices;
        for (int i = 1; i < segments - 1; i++) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        setup_geometry(vertices.data(), vertices.size() * sizeof(Vector3), indices.data(),
                       indices.size() * sizeof(unsigned int));
    }
};


#endif //PROJET_MATHS_5RVJV_CIRCLE_H
