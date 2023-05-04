#pragma once
#include "vector3.hpp"

namespace RayTracing {

// The interface for any texture
class Texture {
public:
    virtual Color value(const double u, const double v, const Point& point) const = 0;
    virtual ~Texture() = default;
};

}