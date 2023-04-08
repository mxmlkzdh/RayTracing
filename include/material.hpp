#pragma once
#include "ray.hpp"
#include "vector3.hpp"

namespace RayTracing {

struct HitRecord;

// The interface for material
class Material {
public:
    virtual bool scatter(const Ray& inRay, const HitRecord& record, const Color& attenuation, const Ray& outRay) const = 0;
    virtual ~Material() {}
};

}