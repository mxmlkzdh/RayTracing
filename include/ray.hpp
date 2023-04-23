#pragma once
#include "vector3.hpp"

namespace RayTracing {

class Ray {
public:
    Point origin;
    Vector3 direction;
    double time;
public:
    Ray() = default;
    Ray(const Point& origin, const Vector3& direction, const double time = 0.0): origin(origin), direction(direction), time(time) {}
    Point at(const double t) const {
        return origin + (t * direction);
    }
};

}