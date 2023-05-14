#pragma once
#include "object.hpp"

namespace RayTracing {

class BVHNode : public Object {
public:
    bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        return false;
    }
    bool boundingBox(const double initTime, const double finalTime, AABB& outputBox) const override {
        return false;
    }
};

}