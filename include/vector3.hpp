#pragma once
#include <cmath>
#include <iostream>

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
using Point3D = Vector3D;
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

}