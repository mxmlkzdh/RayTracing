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
    std::shared_ptr<Texture> emitTexture;
public:
    DiffuseLight(const Color& emitTexture): emitTexture(std::make_shared<SolidColor>(emitTexture)) {}
    DiffuseLight(const std::shared_ptr<Texture> emitTexture): emitTexture(emitTexture) {}
    virtual bool scatter(const Ray&, const HitRecord&, Color&, Ray&) const override {
        return false;
    }
    virtual Color emit(const double u, const double v, const Point& point) const override {
        return emitTexture->value(u, v, point);
    }
};

}