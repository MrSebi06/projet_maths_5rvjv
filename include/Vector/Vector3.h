//
// Created by Sacha TOUTUT on 04/11/2025.
//

#ifndef PROJECT_Vector3_H
#define PROJECT_Vector3_H

#include <iostream>

class Vector3 {
private:
    void swap(Vector3& other);

public:
    float x, y, z;

    Vector3() : x(0), y (0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3(const Vector3& other);
    ~Vector3() = default;

    Vector3& operator=(const Vector3& other);

    Vector3 operator+(const Vector3& other);
    Vector3 operator-(const Vector3& other);
    Vector3 operator*(const float& factor);
    Vector3 operator/(const float& factor);

    float magnitude() const;
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
//    Vector3 perpendicular() const;
};

std::ostream& operator<<(std::ostream& os, const Vector3& v);

#endif //PROJECT_Vector3_H
