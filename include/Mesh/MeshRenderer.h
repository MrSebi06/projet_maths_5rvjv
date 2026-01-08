//
// Created by mihne on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_MESHRENDERER_H
#define PROJET_MATHS_5RVJV_MESHRENDERER_H

#include <memory>

#include "Mesh.h"
#include "Vector/Vector3.h"


class Transform;

class MeshRenderer {
    std::shared_ptr<Mesh> mesh;
    GLuint shader_program;
    Transform *transform;
    Vector3 color;

    GLint loc_model_matrix = -1;
    GLint loc_color = -1;

    bool debug = false;

public:
    MeshRenderer(const std::shared_ptr<Mesh> &mesh, const GLuint shader_program, Transform *transform,
                 const Vector3 &color, const bool debug = false)
        : mesh(mesh),
          shader_program(shader_program),
          transform(transform),
          color(color),
          debug(debug) {
        loc_model_matrix = glGetUniformLocation(shader_program, "model");
        loc_color = glGetUniformLocation(shader_program, "uColor");
    }

    void draw() const;

    void set_color(const Vector3 &color) {
        this->color = color;
    }
};


#endif //PROJET_MATHS_5RVJV_MESHRENDERER_H
