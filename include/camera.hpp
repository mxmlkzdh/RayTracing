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
    Vector3 u;
    Vector3 v;
    Vector3 w;
    double lensRadius;
    double initTime;
    double finalTime;
public:
    Camera(const Point& lookFrom, const Point& lookAt, const Vector3& vUp,
        const double vFoV, const double aspectRatio, const double aperture = 0.0,
        const double focusDistance = 1.0, const double initTime = 0.0, const double finalTime = 0.0): initTime(initTime), finalTime(finalTime) {
        lensRadius = aperture / 2;
        const double theta = Util::degreesToRadians(vFoV);
        const double height = std::tan(theta / 2.0);
        const double viewportHeight = 2.0 * height;
        const double viewportWidth = viewportHeight * aspectRatio;
        w = unitDirection(lookFrom - lookAt);
        u = unitDirection(cross(vUp, w));
        v = cross(w, u);
        origin = lookFrom;
        horizontal = focusDistance * viewportWidth * u;
        vertical = focusDistance * viewportHeight * v;
        lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - (focusDistance * w);
    }
    Ray getRay(const double s, const double t) const {
        if (lensRadius > 0.0) {
            Vector3 rd = lensRadius * randomInUnitDisk();
            Vector3 offset = rd.x * u + rd.y * v;
            return Ray(origin + offset, lowerLeftCorner + (s * horizontal) + (t * vertical) - origin - offset, Util::random(initTime, finalTime));
        } else {
            return Ray(origin, lowerLeftCorner + (s * horizontal) + (t * vertical) - origin, Util::random(initTime, finalTime));
        }
    }
};

}