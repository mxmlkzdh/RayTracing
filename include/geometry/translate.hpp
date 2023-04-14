#pragma once
#include <memory>
#include "../aabb.hpp"
#include "../object.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class Translate: public Object {
public:
    std::shared_ptr<Object> object;
    Vector3 displacement;
public:
    Translate(const std::shared_ptr<Object> object, const Vector3& displacement): object(object), displacement(displacement) {}
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const override {
        Ray movedRay(ray.origin - displacement, ray.direction, ray.time);
        if (!object->hit(movedRay, min, max, record)) {
            return false;
        }
        record.point = record.point + displacement;
        record.setNormal(movedRay, record.normal);
        return true;
    };
    virtual bool boundingBox(const double, const double, AABB& outputBox) const override {
        outputBox = AABB(outputBox.minimum + displacement, outputBox.maximum + displacement);
        return true;
    }
};

}