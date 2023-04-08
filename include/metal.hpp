#pragma once
#include <memory>
#include "vector3.hpp"
#include "object.hpp"
#include "material.hpp"

namespace RayTracing {

class Metal: public Material {
public:
    Color albedo;
    double perturbation = 0;
public:
    Metal(const Color& albedo): albedo(albedo) {}
    Metal(const Color& albedo, const double perturbation): albedo(albedo), perturbation(perturbation < 1 ? perturbation : 1) {}
    virtual ~Metal() {}
    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        Vector3 reflected = reflect(unitDirection(ray.direction), record.normal);
        scatteredRay = Ray(record.point, reflected + perturbation * randomInUnitSphere());
        attenuation = albedo;
        return dot(scatteredRay.direction, record.normal) > 0.0;
    }
};

}