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

    explicit Circle(const float radius, const unsigned int segments) : radius(radius), segments(segments) {
        const double angle = 360.0 / segments;

        std::vector<Vector3> vertices;
        for (unsigned int i = 0; i < segments; i++) {
            const double currentAngle = angle * i;
            double x = radius * cos(deg2rad(currentAngle));
            double y = radius * sin(deg2rad(currentAngle));

            vertices.emplace_back(x, y, 0.0f);
        }

        std::vector<int> indices;
        for (int i = 1; i < segments - 1; i++) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3),
                     vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                     indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


        index_count = indices.size();
    }
};


#endif //PROJET_MATHS_5RVJV_CIRCLE_H
