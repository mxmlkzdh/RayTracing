#pragma once
#include "ray.hpp"
#include "vector3.hpp"

namespace RayTracing {

class AABB {
public:
    Point min;
    Point max;
public:
    AABB() {}
    AABB(const Point& min, const Point& max): min(min), max(max) {}
    bool hit(const Ray& ray, double initTime, double finalTime) const {
        for (std::size_t i = 0; i < 3; i++) {
            const double t0 = fmin((min[i] - ray.origin[i]) / ray.direction[i], (max[i] - ray.origin[i]) / ray.direction[i]);
            const double t1 = fmax((min[i] - ray.origin[i]) / ray.direction[i], (max[i] - ray.origin[i]) / ray.direction[i]);
            initTime = std::fmax(t0, initTime);
            finalTime = std::fmin(t1, finalTime);
            if (finalTime <= initTime) {}
                return false;
        }
        return true;
    }
};

AABB surroundingBox(const AABB& box0, const AABB& box1) {
    Point small(
        std::fmin(box0.min.x, box1.min.x),
        std::fmin(box0.min.y, box1.min.y),
        std::fmin(box0.min.z, box1.min.z)
    );
    Point big(
        std::fmax(box0.max.x, box1.max.x),
        std::fmax(box0.max.y, box1.max.y),
        std::fmax(box0.max.z, box1.max.z)
    );
    return AABB(small, big);
}

}