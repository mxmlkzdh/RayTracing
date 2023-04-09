#pragma once
#include <memory>
#include "../vector3.hpp"
#include "../object.hpp"
#include "../material.hpp"

namespace RayTracing {

class Dielectric: public Material {
public:
    double refractionIndex;
public:
    Dielectric(const double refractionIndex): refractionIndex(refractionIndex) {}
    virtual ~Dielectric() {}
    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refractiveIndicesRation = record.outside ? (1.0 / refractionIndex) : refractionIndex;
        Vector3 unit = unitDirection(ray.direction);
        Vector3 refracted = refract(unit, record.normal, refractiveIndicesRation);
        scatteredRay = Ray(record.point, refracted);
        return true;
    }
};

}