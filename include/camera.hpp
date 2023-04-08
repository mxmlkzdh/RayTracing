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
    Camera(const double vFoV, const double aspectRatio) { // Vertical field-of-view in degrees
        const double THETA = Util::degreesToRadians(vFoV);
        const double H = std::tan(THETA / 2);
        const double VIEWPORT_HEIGHT = 2 * H;
        const double VIEWPORT_WIDTH = VIEWPORT_HEIGHT * aspectRatio;
        ORIGIN = Point(0, 0, 0);
        HORIZONTAL = Vector3(VIEWPORT_WIDTH, 0, 0);
        VERTICAL = Vector3(0, VIEWPORT_HEIGHT, 0);
        LOWER_LEFT_CORNER = ORIGIN - (HORIZONTAL / 2) - (VERTICAL / 2) - Vector3(0, 0, FOCAL_LENGTH);
    }
    Ray getRay(const double u, const double v) const {
        return Ray(ORIGIN, LOWER_LEFT_CORNER + (u * HORIZONTAL) + (v * VERTICAL) - ORIGIN);
    }
};

}