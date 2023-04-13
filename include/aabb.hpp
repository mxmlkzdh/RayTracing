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

AABB surroundingBox(const AABB& box0, const AABB& box1) {
    Point small(
        std::fmin(box0.minimum.x, box1.minimum.x),
        std::fmin(box0.minimum.y, box1.minimum.y),
        std::fmin(box0.minimum.z, box1.minimum.z)
    );
    Point big(
        std::fmax(box0.maximum.x, box1.maximum.x),
        std::fmax(box0.maximum.y, box1.maximum.y),
        std::fmax(box0.maximum.z, box1.maximum.z)
    );
    return AABB(small, big);
}

}