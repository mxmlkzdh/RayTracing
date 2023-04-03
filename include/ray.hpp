#pragma once
#include "vector3.hpp"

namespace RayTracing {

class Ray {
public:
    Point3 origin;
    Vector3 direction;
public:
    Ray(const Point3& origin, const Vector3& direction): origin(origin), direction(direction) {}
    Point3 at(const double t) const {
        return origin + (t * direction);
    }
};

}