#pragma once
#include "../vector3.hpp"
#include "../object.hpp"
#include "../material.hpp"

namespace RayTracing {

class Metal : public Material {
public:
    Color albedo;
    double perturbation;
public:
    Metal(const Color& color) : albedo(color), perturbation(0.0) {}
    Metal(const Color& color, const double perturbation) : albedo(color), perturbation(perturbation < 1 ? perturbation : 1) {}
    bool scatter(const Ray& incidentRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        Vector3 reflected = reflect(incidentRay.direction, record.normal);
        scatteredRay = Ray(record.point, reflected + perturbation * randomInUnitSphere(), incidentRay.time);
        attenuation = albedo;
        return dot(scatteredRay.direction, record.normal) >= 0.0;
    }
};

}