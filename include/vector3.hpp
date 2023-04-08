#pragma once
#include <cmath>
#include <iostream>
#include "util.hpp"

namespace RayTracing {

struct Vector3 {

    double x;
    double y;
    double z;

    Vector3() = default;
    Vector3(const double x, const double y, const double z): x(x), y(y), z(z) {}
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

};

// Type aliases for Vector3
using Point = Vector3;
using Color = Vector3;

bool operator==(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
bool operator!=(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}
Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}
Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
Vector3 operator-(const Vector3& vector) {
    return Vector3(-vector.x, -vector.y, -vector.z);
}
Vector3 operator*(const double t, const Vector3& vector) {
    return Vector3(t * vector.x, t * vector.y, t * vector.z);
}
Vector3 operator/(const Vector3& vector, const double t) {
    return Vector3(vector.x / t, vector.y / t, vector.z / t);
}

double dot(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
    return Vector3(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
}
Vector3 unitDirection(const Vector3& vector) {
    return vector / vector.length();
}
inline Vector3 random() {
    return Vector3(Util::random(), Util::random(), Util::random());
}
inline Vector3 random(const double min, const double max) {
    return Vector3(Util::random(min, max), Util::random(min, max), Util::random(min, max));
}
inline Vector3 randomInUnitSphere() {
    while (true) {
        Vector3 rand = random(-1, 1);
        if (rand.length() < 1) {
            return rand;
        }
    }
    return Vector3();
}
inline Vector3 randomUnitVector() {
    return unitDirection(randomInUnitSphere());
}

}