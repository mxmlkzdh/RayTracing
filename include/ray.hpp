#pragma once
#include "vector3d.hpp"

namespace RayTracing {

class Ray {
public:
    Point origin;
    Vector3D direction;
public:
    Ray(const Point& origin, const Vector3D& direction): origin(origin), direction(direction) {}
    Point at(const double t) const {
        return origin + (t * direction);
    }
    Point operator[](const double t) const {
        return origin + (t * direction);
    }
};

}