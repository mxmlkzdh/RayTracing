#pragma once
#include <cmath>
#include <iostream>

namespace RayTracing {

class Vector3 {
public:
    double x, y, z;
public:
    Vector3(): x(0), y(0), z(0) {}
    Vector3(const double x, const double y, const double z): x(x), y(y), z(z) {}
    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

// Type aliases for Vector3
using Point3 = Vector3;
using Color = Vector3;

// Vector3 Utility Operators and Functions
std::ostream& operator<<(std::ostream& ostream, const Vector3& vector) {
    return ostream << '[' << vector.x << ", " << vector.y << ", " << vector.z << ']';
}
bool operator==(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
bool operator!=(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}
Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}
Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}
Vector3 operator-(const Vector3& vector) {
    return {-vector.x, -vector.y, -vector.z};
}
Vector3 operator*(const double t, const Vector3& vector) {
    return {t * vector.x, t * vector.y, t * vector.z};
}
Vector3 operator/(const Vector3& vector, const double t) {
    return {vector.x / t, vector.y / t, vector.z / t};
}

double dot(const Vector3& lhs, const Vector3& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
    return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x};
}
Vector3 unit(const Vector3& vector) {
    return vector / vector.length();
}

}