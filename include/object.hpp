#pragma once
#include <memory>
#include "ray.hpp"
#include "vector3.hpp"
#include "material.hpp"

namespace RayTracing {

struct HitRecord {
    double time;
    Point point;
    Vector3 normal;
    bool outside;
    std::shared_ptr<Material> material;
    inline void setNormal(const Ray& ray, const Vector3& outwardNormal) {
        outside = dot(ray.direction, outwardNormal) < 0;
        normal = outside ? outwardNormal : -outwardNormal;
    }
};

// The interface for a hittable object
class Object {
public:
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const = 0;
    virtual ~Object() {}
};

}