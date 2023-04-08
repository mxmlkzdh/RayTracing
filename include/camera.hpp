#pragma once
#include <cmath>
#include "ray.hpp"
#include "util.hpp"
#include "vector3.hpp"

namespace RayTracing {

class Camera {
private:
    const double FOCAL_LENGTH = 1.0;
    Point ORIGIN;
    Vector3 HORIZONTAL;
    Vector3 VERTICAL;
    Vector3 LOWER_LEFT_CORNER;
public:
    Camera(const Point& lookFrom, const Point& lookAt, const Vector3& vUp, const double vFoV, const double aspectRatio) { // Vertical field-of-view in degrees
        const double THETA = Util::degreesToRadians(vFoV);
        const double H = std::tan(THETA / 2);
        const double VIEWPORT_HEIGHT = 2 * H;
        const double VIEWPORT_WIDTH = VIEWPORT_HEIGHT * aspectRatio;

        Vector3 w = unitDirection(lookFrom - lookAt);
        Vector3 u = unitDirection(cross(vUp, w));
        Vector3 v = cross(w, u);

        ORIGIN = lookFrom;
        HORIZONTAL = VIEWPORT_WIDTH * u;
        VERTICAL = VIEWPORT_HEIGHT * v;
        LOWER_LEFT_CORNER = ORIGIN - (HORIZONTAL / 2) - (VERTICAL / 2) - w;
    }
    Ray getRay(const double u, const double v) const {
        return Ray(ORIGIN, LOWER_LEFT_CORNER + (u * HORIZONTAL) + (v * VERTICAL) - ORIGIN);
    }
};

}