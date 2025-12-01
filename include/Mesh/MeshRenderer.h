//
// Created by mihne on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_MESHRENDERER_H
#define PROJET_MATHS_5RVJV_MESHRENDERER_H

#include <memory>

#include "Mesh.h"
#include "Vector/Vector3.h"


class MeshRenderer {
    std::shared_ptr<Mesh> mesh;
    GLuint shader_program;
    Vector2 *position;
    Vector3 color;

    GLint loc_offset = -1;
    GLint loc_color = -1;

public:
    MeshRenderer(const std::shared_ptr<Mesh> &mesh, const GLuint shader_program, Vector2 *position,
                 const Vector3 &color) : mesh(mesh), shader_program(shader_program), position(position), color(color) {
        loc_offset = glGetUniformLocation(shader_program, "uOffset");
        loc_color = glGetUniformLocation(shader_program, "uColor");
    }

    void draw() const;
};


#endif //PROJET_MATHS_5RVJV_MESHRENDERER_H
