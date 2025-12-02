//
// Created by mihne on 02/12/2025.
//

#ifndef PROJET_MATHS_5RVJV_TRANSFORM_H
#define PROJET_MATHS_5RVJV_TRANSFORM_H
#include "Vector/Vector2.h"


class Transform {
    friend class Rigidbody2D;

protected:
    Vector2 position;
    float rotation;

public:
    Transform(const Vector2 &position, const float rotation)
        : position(position),
          rotation(rotation) {}

    const Vector2 &getPosition() const { return position; }
    float getRotation() const { return rotation; }

    void addPosition(const Vector2 &position_);
};


#endif //PROJET_MATHS_5RVJV_TRANSFORM_H
