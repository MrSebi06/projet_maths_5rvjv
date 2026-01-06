//
// Created by mihne on 01/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_GAMEOBJECT_H
#define PROJET_MATHS_5RVJV_GAMEOBJECT_H

#include <memory>

#include "Mesh/MeshRenderer.h"
#include "Vector/Vector2.h"
#include "Physics/Rigidbody.h"
#include "Transform.h"

class Rigidbody2D;

class GameObject {
    Transform transform;

    std::unique_ptr<MeshRenderer> renderer = nullptr;
    std::unique_ptr<Rigidbody2D> body = nullptr;

public:
    explicit GameObject(const Vector2 &position, const float rotation = 0.0)
        : transform{
            Transform(position, rotation)
        } {};

    void draw() const;
    void add_renderer(const std::shared_ptr<Mesh> &mesh, GLuint shader, const Vector3 &color);
    void add_rigidbody(const float &mass,
                       const float &restitution,
                       float friction,
                       CollisionShape *shape,
                       bool debug = false);
    void add_liquidbody(const float &mass,
                        const float &restitution,
                        float friction,
                        CollisionShape *shape,
                        bool debug = false);

    Rigidbody2D *get_rigidbody() const { return body.get(); }
    Vector2 get_position() const { return transform.getPosition(); }
};


#endif //PROJET_MATHS_5RVJV_GAMEOBJECT_H
