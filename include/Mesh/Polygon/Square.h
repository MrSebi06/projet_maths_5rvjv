//
// Created by mihne on 03/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_SQUARE_H
#define PROJET_MATHS_5RVJV_SQUARE_H


#include "Mesh/Mesh.h"

class SquareMesh : public Mesh {
public:
    float size;

    explicit SquareMesh(const float size_) : size(size_ / 2) {
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
