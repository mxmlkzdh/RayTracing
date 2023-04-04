#pragma once
#include "ray.hpp"
#include "vector3d.hpp"

namespace RayTracing {

class Camera {
private:
    Point origin;
    Vector3D horizontal;
    Vector3D vertical;
    Vector3D lowerLeftCorner;
public:
    Camera() {
        const double aspectRatio = 16.0 / 9.0;
        const double viewportHeight = 2.0;
        const double viewportWidth = aspectRatio * viewportHeight;
        const double focalLength = 1.0;
        origin = {0, 0, 0};
        horizontal = {viewportWidth, 0, 0};
        vertical = {0, viewportHeight, 0};
        lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - Vector3D(0, 0, focalLength);
    }
    Ray getRay(const double u, const double v) {
        Ray ray(origin, lowerLeftCorner + (u * horizontal) + (v * vertical) - origin);
        return ray;
    }
};

}