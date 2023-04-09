#pragma once
#include <cmath>
#include "../vector3.hpp"
#include "../texture.hpp"
#include "solid_color.hpp"

namespace RayTracing {

class CheckerTexture: public Texture {
public:
    std::shared_ptr<Texture> even;
    std::shared_ptr<Texture> odd;
public:
    CheckerTexture() {}
    CheckerTexture(const std::shared_ptr<Texture> even, const std::shared_ptr<Texture> odd): even(even), odd(odd) {}
    CheckerTexture(const Color& even, const Color& odd): even(std::make_shared<SolidColor>(even)), odd(std::make_shared<SolidColor>(odd)) {}
    virtual ~CheckerTexture() {}
    virtual Color value(const double u, const double v, const Point& point) const override {
        const double sines = std::sin(10.0 * point.x) * std::sin(10.0 * point.y) * std::sin(10.0 * point.z);
        if (sines < 0) {
            return odd->value(u, v, point);
        } else {

            return even->value(u, v, point);
        }
    }
};

}