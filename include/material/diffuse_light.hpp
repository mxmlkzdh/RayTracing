#pragma once
#include <memory>
#include "../vector3.hpp"
#include "../object.hpp"
#include "../material.hpp"
#include "../texture.hpp"
#include "../texture/solid_color.hpp"

namespace RayTracing {

class DiffuseLight: public Material {
public:
    std::shared_ptr<Texture> emit;
public:
    DiffuseLight(const Color& emit): emit(std::make_shared<SolidColor>(emit)) {}
    DiffuseLight(const std::shared_ptr<Texture> emit): emit(emit) {}
    virtual bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scatteredRay) const override {
        return false;
    }
    virtual Color emit(const double u, const double v, const Point& point) const override {
        return emit->value(u, v, point);
    }
};

}