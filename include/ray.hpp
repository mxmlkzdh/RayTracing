#pragma once
#include "vector3.hpp"

namespace RayTracing {

struct Ray {

    Point origin;
    Vector3 direction;

    Ray(const Point& origin, const Vector3& direction):origin(origin), direction(direction) {}
    Point at(const double t) const {
        return origin + t * direction;
    }

};

}