#pragma once
#include "vector3.hpp"
#include "ray.hpp"

namespace RayTracing {

struct HitRecord;

class Material {
    virtual bool scatter(const Ray& inRay, const HitRecord& record, const Color& attenuation, const Ray& outRay) const = 0;
};

}