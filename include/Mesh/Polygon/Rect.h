//
// Created by mihne on 03/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_RECT_H
#define PROJET_MATHS_5RVJV_RECT_H


#include "Mesh/Mesh.h"

class RectMesh : public Mesh {
public:
    float w;
    float h;

    explicit RectMesh(const float width, const float height) : w(width / 2), h(height / 2) {
        const Vector2 vertices[4] = {
            {w, h}, // TR
            {w, -h}, // BR
            {-w, -h}, // BL
            {-w, h} // TL
        };
        const unsigned int indices[6] = {
            0, 1, 2,
            0, 2, 3
        };

        setup_geometry(vertices, 4 * sizeof(Vector2), indices,
                       6 * sizeof(unsigned int));
    }
};


#endif //PROJET_MATHS_5RVJV_RECT_H
