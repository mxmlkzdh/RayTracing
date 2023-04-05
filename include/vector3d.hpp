#pragma once
#include <cmath>
#include <iostream>
#include "common.hpp"

namespace RayTracing {

class Vector3D {
public:
    double x, y, z;
public:
    Vector3D(): x(0), y(0), z(0) {}
    Vector3D(const double x, const double y, const double z): x(x), y(y), z(z) {}
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

// Type aliases for Vector3D
using Point = Vector3D;
using Color = Vector3D;

// Vector3D Utility Operators and Functions
std::ostream& operator<<(std::ostream& ostream, const Vector3D& vector) {
    return ostream << '[' << vector.x << ", " << vector.y << ", " << vector.z << ']';
}
bool operator==(const Vector3D& lhs, const Vector3D& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
bool operator!=(const Vector3D& lhs, const Vector3D& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}
Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}
Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}
Vector3D operator-(const Vector3D& vector) {
    return {-vector.x, -vector.y, -vector.z};
}
Vector3D operator*(const double t, const Vector3D& vector) {
    return {t * vector.x, t * vector.y, t * vector.z};
}
Vector3D operator/(const Vector3D& vector, const double t) {
    return {vector.x / t, vector.y / t, vector.z / t};
}

double dot(const Vector3D& lhs, const Vector3D& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
Vector3D cross(const Vector3D& lhs, const Vector3D& rhs) {
    return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
}
Vector3D unit(const Vector3D& vector) {
    return vector / vector.length();
}

static Vector3D random() {
    return Vector3D(randomDouble(), randomDouble(), randomDouble());
}

static Vector3D random(double min, double max) {
    return Vector3D(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

static Vector3D randomInUnitSphere() {
    while (true) {
        Vector3D randomVector = random(-1, 1);
        if (dot(randomVector, randomVector) >= 1) continue;
        return randomVector;
    }
}

static Vector3D randomUnitSphere() {
    return unit(randomInUnitSphere());
}

Vector3D randomInHemisphere(const Vector3D& normal) {
    Vector3D inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0.0) { // In the same hemisphere as the normal

        return inUnitSphere;
    } else {
        return -inUnitSphere;
    }
}

}