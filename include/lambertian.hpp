#pragma once
#include <memory>
#include "vector3.hpp"
#include "material.hpp"

namespace RayTracing {

class Lambertian: public Material {
public:
    Color albedo;
public:
    Lambertian(const Color& albedo): albedo(albedo) {};
    virtual ~Lambertian() {}
    virtual bool scatter(const Ray& inRay, const HitRecord& record, Color& attenuation, Ray& outRay) const override {
        Vector3 scatterDirection = record.normal + randomUnitVector();
        if (nearZero(scatterDirection)) {
            scatterDirection = record.normal;
        }
        outRay = Ray(record.point, scatterDirection);
        attenuation = albedo;
        return true;
    }
};

}