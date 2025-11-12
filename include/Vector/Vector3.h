//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJECT_Vector3_H
#define PROJECT_Vector3_H

#include <iostream>

struct Vector3 {
    float x, y, z;

    void swap(Vector3 &other) noexcept;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
    Vector3(const Vector3 &other);
    ~Vector3() = default;

    Vector3 &operator=(const Vector3 &other);

    Vector3 operator+(const Vector3 &other) const;
    Vector3 operator-(const Vector3 &other) const;
    Vector3 operator*(const float &factor) const;
    Vector3 operator/(const float &factor) const;

    float magnitude() const;
    float dot(const Vector3 &other) const;
    Vector3 cross(const Vector3 &other) const;
    // Vector3 perpendicular() const;
};

std::ostream &operator<<(std::ostream &os, const Vector3 &v);

#endif //PROJECT_Vector3_H
