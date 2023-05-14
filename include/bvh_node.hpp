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
        if (!box.hit(ray, min, max)) {
            return false;
        }
        bool hitLeft = left->hit(ray, min, max, record);
        bool hitRight = right->hit(ray, min, hitLeft ? record.time : max, record);
        return hitLeft || hitRight;
    }
    bool boundingBox(const double initTime, const double finalTime, AABB& outputBox) const override {
        return false;
    }
};

}