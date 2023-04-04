#pragma once
#include "ray.hpp"

namespace RayTracing {

struct HitRecord {
    Point point;
    double t;
    bool frontFace;
    Vector3D normal;
    void setFaceNormal(const Ray& ray, const Vector3D& outwardNormal) {
        frontFace = dot(ray.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual bool hit(const Ray& ray, const double min, const double max, HitRecord& record) const = 0;
};

}