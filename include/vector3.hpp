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
    Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {}
    double& operator[](const std::size_t i) {
        if (i == 0) return x;
        else if (i == 1) return y;
        else if (i == 2) return z;
        else throw("Out of Bounds.");
    }
    double operator[](const std::size_t i) const {
        if (i == 0) return x;
        else if (i == 1) return y;
        else if (i == 2) return z;
        else throw("Out of Bounds.");
    }
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

};

// Type aliases for Vector3
using UnitVector = Vector3;
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
Vector3 operator*(const Vector3& lhs, const Vector3& rhs) {
    return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
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
UnitVector unitDirection(const Vector3& vector) {
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
        Vector3 rand = random(-1.0, 1.0);
        if (rand.length() < 1) {
            return rand;
        }
    }
    return Vector3();
}
inline UnitVector randomUnitVector() {
    const double theta = 2.0 * Constants::PI * Util::random();
    const double phi = std::acos(1 - 2 * Util::random());
    return Vector3(std::sin(phi) * std::cos(theta), std::sin(phi) * std::sin(theta), std::cos(phi));
}
inline Vector3 randomInHemisphere(const Vector3 normal) {
    Vector3 rand = randomInUnitSphere();
    if (dot(rand, normal) > 0.0) { // In the same hemisphere as the normal.
        return rand;
    } else {
        return -rand;
    }
}
inline Vector3 randomInUnitDisk() {
    while (true) {
        Vector3 rand(Util::random(-1.0, 1.0), Util::random(-1.0, 1.0), 0.0);
        if (rand.length() < 1) {
            return rand;
        }
    }
    return Vector3();
}

inline bool nearZero(const Vector3& vector) {
    const double LIMIT = 1e-8;
    return (std::fabs(vector.x) < LIMIT) && (std::fabs(vector.y) < LIMIT) && (std::fabs(vector.z) < LIMIT);
}

Vector3 reflect(const Vector3& vector, const UnitVector& normal) {
    return vector - 2 * dot(vector, normal) * normal;
}
Vector3 refract(const Vector3& vector, const Vector3& normal, const double refractiveIndicesRatio) {
    double cosTheta = std::fmin(dot(-vector, normal), 1.0);
    Vector3 perpendicularRay = refractiveIndicesRatio * (vector + (cosTheta * normal));
    Vector3 parallelRay = -std::sqrt(std::fabs(1.0 - dot(perpendicularRay, perpendicularRay))) * normal;
    return perpendicularRay + parallelRay;
}

}