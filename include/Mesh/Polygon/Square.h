//
// Created by mihne on 03/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_SQUARE_H
#define PROJET_MATHS_5RVJV_SQUARE_H


#include <cmath>
#include <vector>

#include "helpers.h"
#include "Mesh/Mesh.h"
#include "Vector/Vector3.h"


class Square : public Mesh {
public:
    float size;

    explicit Square(const float size) : size(size) {
        const Vector2 vertices[4] = {
            {size, size}, // TR
            {size, -size}, // BR
            {-size, -size}, // BL
            {-size, size} // TL
        };
        const unsigned int indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        setup_geometry(vertices, 4 * sizeof(Vector2), indices,
                       6 * sizeof(unsigned int));
    }
};


#endif //PROJET_MATHS_5RVJV_SQUARE_H
