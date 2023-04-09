#pragma once
#include <memory>
#include "vector3.hpp"
#include "object.hpp"
#include "material.hpp"

namespace RayTracing {

class Lambertian: public Material {
public:
    Color albedo;
public:
    Lambertian(const Color& albedo): albedo(albedo) {};
    virtual ~Lambertian() {}
    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        Vector3 scatterDirection = record.normal + randomInUnitSphere();
        if (nearZero(scatterDirection)) {
            scatterDirection = record.normal;
        }
        scatteredRay = Ray(record.point, scatterDirection);
        attenuation = albedo;
        return true;
    }
};

}