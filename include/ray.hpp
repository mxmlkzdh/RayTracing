#pragma once
#include "vector3.hpp"

namespace RayTracing {

class Ray {
public:
    Point origin;
    Vector3 direction;
public:
    Ray() {}
    Ray(const Point& origin, const Vector3& direction):origin(origin), direction(direction) {}
    Point at(const double t) const {
        return origin + (t * direction);
    }
};

}