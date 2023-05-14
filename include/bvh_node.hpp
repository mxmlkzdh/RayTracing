#pragma once
#include <memory>
#include "object.hpp"
#include "aabb.hpp"

namespace RayTracing {

class BVHNode : public Object {
public:
    std::shared_ptr<Object> left;
    std::shared_ptr<Object> right;
    AABB box;
public:
    bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        return false;
    }
    bool boundingBox(const double initTime, const double finalTime, AABB& outputBox) const override {
        return false;
    }
};

}