#pragma once
#include <memory>
#include "../vector3.hpp"
#include "../material.hpp"
#include "../texture.hpp"
#include "../texture/solid_color.hpp"

namespace RayTracing {

class DiffuseLight: public Material {
public:
    std::shared_ptr<Texture> emitTexture;
public:
    DiffuseLight(const Color& color): emitTexture(std::make_shared<SolidColor>(color)) {}
    DiffuseLight(const std::shared_ptr<Texture> emitTexture): emitTexture(emitTexture) {}
    bool scatter(const Ray&, const HitRecord&, Color&, Ray&) const override {
        return false;
    }
    Color emit(const double u, const double v, const Point& point) const override {
        return emitTexture->value(u, v, point);
    }
};

}