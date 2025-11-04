//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include "../Vector3.h"
#include <algorithm>
#include <cmath>

void Vector3::swap(Vector3 &other) {
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(z, other.z);
}

Vector3::Vector3(const Vector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

Vector3 &Vector3::operator=(const Vector3 &other) {
    Vector3 tmp = other;
    swap(tmp);
    return *this;
}

Vector3 Vector3::operator+(const Vector3 &other) {
    return {x + other.x, y + other.y, z + other.z};
}

Vector3 Vector3::operator-(const Vector3 &other) {
    return {x - other.x, y - other.y, z - other.z};
}

Vector3 Vector3::operator*(const float &factor) {
    return {x * factor, y * factor, z * factor};
}

Vector3 Vector3::operator/(const float &factor) {
    return {x / factor, y / factor, z / factor};
}

float Vector3::magnitude() const {
    return std::sqrt(x*x + y*y + z*z);
}

float Vector3::dot(const Vector3 &other) const {
    return x*other.x + y*other.y + z*other.z;
}

Vector3 Vector3::cross(const Vector3 &other) const {
    return {
        y * other.z - other.y * z,
        z * other.x - other.z * x,
        x * other.y - other.x * y,
    };
}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
    os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}
