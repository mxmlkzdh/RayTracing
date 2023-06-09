#pragma once
#include <memory>
#include "../vector3.hpp"
#include "../object.hpp"
#include "../material.hpp"

namespace RayTracing {

class Dielectric : public Material {
public:
    double refractionIndex;
public:
    Dielectric(const double refractionIndex) : refractionIndex(refractionIndex) {}
    bool scatter(const Ray& incidentRay, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refractiveIndicesRatio = record.outside ? (1.0 / refractionIndex) : refractionIndex;
        Vector3 unit = unitDirection(incidentRay.direction);
        double cosTheta = std::fmin(dot(-unit, record.normal), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
        bool cannotRefract = refractiveIndicesRatio * sinTheta > 1.0;
        Vector3 direction;
        if (cannotRefract || reflectance(cosTheta, refractiveIndicesRatio) > Util::random()) {
            direction = reflect(unit, record.normal);
        } else {
            direction = refract(unit, record.normal, refractiveIndicesRatio);
        }
        scatteredRay = Ray(record.point, direction, incidentRay.time);
        return true;
    }
private:
    static double reflectance(const double cosine, const double refractionIndex) {
        // Use Schlick's approximation for reflectance.
        double r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};

}