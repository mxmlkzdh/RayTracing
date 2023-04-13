#pragma once
#include "ray.hpp"
#include "vector3.hpp"

namespace RayTracing {

class AABB {
public:
    Point minimum;
    Point maximum;
public:
    AABB() {}
    AABB(const Point& minimum, const Point& maximum): minimum(minimum), maximum(maximum) {}
    bool hit(const Ray& ray, double initTime, double finalTime) const {
        for (std::size_t i = 0; i < 3; i++) {
            const double t0 = fmin((minimum[i] - ray.origin[i]) / ray.direction[i], (maximum[i] - ray.origin[i]) / ray.direction[i]);
            const double t1 = fmax((minimum[i] - ray.origin[i]) / ray.direction[i], (maximum[i] - ray.origin[i]) / ray.direction[i]);
            initTime = std::fmax(t0, initTime);
            finalTime = std::fmin(t1, finalTime);
            if (finalTime <= initTime)
                return false;
        }
        return true;
    }
};

}