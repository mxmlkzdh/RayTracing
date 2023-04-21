#pragma once
#include "../vector3.hpp"
#include "../texture.hpp"

namespace RayTracing {

class SolidColor: public Texture {
public:
    Color color;
public:
    SolidColor() {}
    SolidColor(const Color& color): color(color) {}
    SolidColor(const double red, const double green, const double blue): color(Color(red, green, blue)) {}
    virtual Color value(const double, const double, const Point&) const override {
        return color;
    }
};

}