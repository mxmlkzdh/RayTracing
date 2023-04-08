#pragma once
#include <cmath>
#include "ray.hpp"
#include "util.hpp"
#include "vector3.hpp"

namespace RayTracing {

class Camera {
private:
    Point origin;
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 lowerLeftCorner;
public:
    Camera(const Point& lookFrom, const Point& lookAt, const Vector3& vUp, const double vFoV, const double aspectRatio) {
        const double theta = Util::degreesToRadians(vFoV);
        const double h = std::tan(theta / 2.0);
        const double viewportHeight = 2.0 * h;
        const double viewportWidth = viewportHeight * aspectRatio;
        const Vector3 w = unitDirection(lookFrom - lookAt);
        const Vector3 u = unitDirection(cross(vUp, w));
        const Vector3 v = cross(w, u);
        origin = lookFrom;
        horizontal = viewportWidth * u;
        vertical = viewportHeight * v;
        lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - w;
    }
    Ray getRay(const double u, const double v) const {
        return Ray(origin, lowerLeftCorner + (u * horizontal) + (v * vertical) - origin);
    }
};

}