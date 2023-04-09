#pragma once
#include <memory>
#include "ray.hpp"
#include "vector3.hpp"
#include "material.hpp"

namespace RayTracing {

struct HitRecord {
    double time;
    Point point;
    Vector3 normal; // Design Decision: The surface (unit) normal vector will always point against the incoming ray direction.
    bool outside;
    double u; // U,V surface coordinates
    double v; // U,V surface coordinates
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