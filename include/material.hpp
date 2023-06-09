#pragma once
#include "ray.hpp"
#include "vector3.hpp"

namespace RayTracing {

struct HitRecord;

// The interface for any material
class Material {
public:
    virtual bool scatter(const Ray& incidentRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const = 0;
    virtual Color emit(const double, const double, const Point&) const {
        return Color(0.0, 0.0, 0.0);
    }
    virtual ~Material() = default;
};

}