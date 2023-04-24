#pragma once
#include <memory>
#include "../vector3.hpp"
#include "../object.hpp"
#include "../material.hpp"
#include "../texture.hpp"
#include "../texture/solid_color.hpp"

namespace RayTracing {

class Lambertian: public Material {
public:
    std::shared_ptr<Texture> albedo;
public:
    Lambertian(const Color& albedo): albedo(std::make_shared<SolidColor>(albedo)) {}
    Lambertian(const std::shared_ptr<Texture> albedo): albedo(albedo) {}
    bool scatter(const Ray& incidentRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        Vector3 scatterDirection = record.normal + randomUnitVector();
        if (nearZero(scatterDirection)) { // Catch degenerate scatter directions
            scatterDirection = record.normal;
        }
        scatteredRay = Ray(record.point, scatterDirection, incidentRay.time);
        attenuation = albedo->value(record.u, record.v, record.point);
        return true;
    }
};

}