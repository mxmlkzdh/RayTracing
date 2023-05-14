#pragma once
#include <cmath>
#include "solid_color.hpp"
#include "../vector3.hpp"
#include "../texture.hpp"

namespace RayTracing {

class CheckerTexture : public Texture {
public:
    std::shared_ptr<Texture> even;
    std::shared_ptr<Texture> odd;
    double size;
public:
    CheckerTexture(const std::shared_ptr<Texture> even, const std::shared_ptr<Texture> odd, const double size = 10.0) : even(even), odd(odd), size(size) {}
    CheckerTexture(const Color& even, const Color& odd, const double size = 10) : even(std::make_shared<SolidColor>(even)), odd(std::make_shared<SolidColor>(odd)), size(size) {}
    Color value(const double u, const double v, const Point& point) const override {
        const double sines = std::sin(size * point.x) * std::sin(size * point.y) * std::sin(size * point.z);
        if (sines < 0) {
            return odd->value(u, v, point);
        } else {
            return even->value(u, v, point);
        }
    }
};

}