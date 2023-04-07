#pragma once
#include "ray.hpp"
#include "vector3.hpp"

namespace RayTracing {

struct HitRecord {
    double time;
    Point point;
    Vector3 normal;
    inline void setNormal(const Ray& ray, const Vector3& outwardNormal) {
        outside = dot(ray.direction, outwardNormal) < 0;
        normal = outside ? outwardNormal : -outwardNormal;
    }
private:
    bool outside;
};

// The interface for a hittable object
class Object {
public:
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const = 0;
    virtual ~Object() {}
};

}