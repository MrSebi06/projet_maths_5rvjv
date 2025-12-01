//
// Created by Sacha TOUTUT on 04/11/2025.
//

#include "Vector/Vector2.h"

#include <algorithm>
#include <cmath>

void Vector2::swap(Vector2 &other) noexcept {
    std::swap(x, other.x);
    std::swap(y, other.y);
}

Vector2::Vector2(const Vector2 &other) {
    x = other.x;
    y = other.y;
}

Vector2 &Vector2::operator=(const Vector2 &other) {
    Vector2 tmp = other;
    swap(tmp);
    return *this;
}

Vector2 Vector2::operator+(const Vector2 &other) {
    return {x + other.x, y + other.y};
}

Vector2 Vector2::operator-(const Vector2 &other) {
    return {x - other.x, y - other.y};
}

Vector2 Vector2::operator*(const float &factor) {
    return {x * factor, y * factor};
}

Vector2 Vector2::operator/(const float &factor) const {
    return {x / factor, y / factor};
}

Vector2 &Vector2::operator+=(const Vector2 &other) {
    Vector2 tmp = *this + other;
    swap(tmp);
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other) {
    Vector2 tmp = *this - other;
    swap(tmp);
    return *this;
}

Vector2 &Vector2::operator*=(const float &factor) {
    Vector2 tmp = *this * factor;
    swap(tmp);
    return *this;
}

Vector2 &Vector2::operator/=(const float &factor) {
    Vector2 tmp = *this / factor;
    swap(tmp);
    return *this;
}

float Vector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::dot(const Vector2 &other) const {
    return x * other.x + y * other.y;
}

float Vector2::cross(const Vector2 &other) const {
    return x * other.y - y * other.x;
}

Vector2 Vector2::rotation(const float &angle) const {
    return {
        x * cosf(angle) - y * sinf(angle),
        x * sinf(angle) + y * cosf(angle)
    };
}

Vector2 Vector2::perpendicular() const {
    return {-y, x};
}

Vector2 Vector2::normalized() const {
    return *this / magnitude();
}

std::ostream &operator<<(std::ostream &os, const Vector2 &v) {
    os << "Vector2(" << v.x << ", " << v.y << ")";
    return os;
}
