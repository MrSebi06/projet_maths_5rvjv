//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJECT_VECTOR2_H
#define PROJECT_VECTOR2_H

#include <iostream>

struct Vector2 {
    float x, y;

    void swap(Vector2 &other) noexcept;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}
    Vector2(const Vector2 &other);
    ~Vector2() = default;

    Vector2 &operator=(const Vector2 &other);

    Vector2 operator+(const Vector2 &other);
    Vector2 operator-(const Vector2 &other);
    Vector2 operator*(const float &factor);
    Vector2 operator/(const float &factor);

    Vector2 &operator+=(const Vector2 &other);
    Vector2 &operator-=(const Vector2 &other);
    Vector2 &operator*=(const float &other);
    Vector2 &operator/=(const float &other);

    float magnitude() const;
    float dot(const Vector2 &other) const;
    float cross(const Vector2 &other) const;
    Vector2 rotation(const float &angle) const;
    Vector2 perpendicular() const;

    float getX() const { return x; }
    float getY() const { return y; }
};

std::ostream &operator<<(std::ostream &os, const Vector2 &v);

#endif //PROJECT_VECTOR2_H
