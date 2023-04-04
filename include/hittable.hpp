#pragma once
#include "ray.hpp"

namespace RayTracing {

struct HitRecord {
    Point3D point;
    double t;
    Vector3D normal;
};

class Hittable {
public:
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const = 0;
};

}