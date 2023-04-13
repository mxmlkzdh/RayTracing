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
    bool hit(const Ray& ray, double minTime, double maxTime) const {
        for (int i = 0; i < 3; i++) {
            double t0 = fmin((minimum[i] - ray.origin[i]) / ray.direction[i], (maximum[i] - ray.origin[i]) / ray.direction[i]);
            double t1 = fmax((minimum[i] - ray.origin[i]) / ray.direction[i], (maximum[i] - ray.origin[i]) / ray.direction[i]);
            minTime = std::fmax(t0, minTime);
            minTime = std::fmin(t1, maxTime);
            if (minTime <= minTime)
                return false;
        }
        return true;
    }
};

}