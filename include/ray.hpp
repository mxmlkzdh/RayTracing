#pragma once
#include "vector3d.hpp"

namespace RayTracing {

class Ray {
public:
    Point3D origin;
    Vector3D direction;
public:
    Ray(const Point3D& origin, const Vector3D& direction): origin(origin), direction(direction) {}
    Point3D at(const double t) const {
        return origin + (t * direction);
    }
    Point3D operator[](const double t) const {
        return origin + (t * direction);
    }
};

}