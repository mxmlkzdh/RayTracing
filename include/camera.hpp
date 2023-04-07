#pragma once
#include "ray.hpp"
#include "vector3.hpp"

namespace RayTracing {

class Camera {
private:
    const double ASPECT_RATIO = 16.0 / 9.0;
    const double FOCAL_LENGTH = 1.0;
    const double VIEWPORT_WIDTH = 4.0;
    const double VIEWPORT_HEIGHT = VIEWPORT_WIDTH / ASPECT_RATIO;
    const Point ORIGIN = Point(0, 0, 0);
    const Vector3 HORIZONTAL = Vector3(VIEWPORT_WIDTH, 0, 0);
    const Vector3 VERTICAL = Vector3(0, VIEWPORT_HEIGHT, 0);
    const Vector3 LOWER_LEFT_CORNER = ORIGIN - (HORIZONTAL / 2) - (VERTICAL / 2) - Vector3(0, 0, FOCAL_LENGTH);
public:
    Camera() = default;
    Ray getRay(const double u, const double v) const {
        return Ray(ORIGIN, LOWER_LEFT_CORNER + (u * HORIZONTAL) + (v * VERTICAL) - ORIGIN);
    }
};

}