//
// Created by mihne on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_GAMEOBJECT_H
#define PROJET_MATHS_5RVJV_GAMEOBJECT_H

#include <memory>

#include "Mesh/MeshRenderer.h"
#include "Vector/Vector2.h"


class GameObject {
    Vector2 position;

    std::unique_ptr<MeshRenderer> renderer;

public:
    void draw() const;

    void add_renderer(const std::shared_ptr<Mesh> &mesh, GLuint shader, const Vector3 &color);
};


#endif //PROJET_MATHS_5RVJV_GAMEOBJECT_H
