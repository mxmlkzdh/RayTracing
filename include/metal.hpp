#pragma once
#include <memory>
#include "vector3.hpp"
#include "object.hpp"
#include "material.hpp"

namespace RayTracing {

class Metal: public Material {
public:
    Color albedo;
public:
    Metal(const Color& albedo): albedo(albedo) {};
    virtual ~Metal() {}
    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        Vector3 reflected = reflect(unitDirection(ray.direction), record.normal);
        scatteredRay = Ray(record.point, reflected);
        attenuation = albedo;
        return dot(scatteredRay.direction, record.normal) > 0.0;
    }
};

}