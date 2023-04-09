#pragma once
#include "object.hpp"
#include "vector3.hpp"
#include "constants.hpp"

namespace RayTracing {

Color computeRayColor(const Ray& ray, const Object& world, const int depth) {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth == 0) {
        return Color(0, 0, 0);
    }
    HitRecord record;
    if (world.hit(ray, 0.001, Constants::DOUBLE_INFINITY, record)) {
        Ray scatteredRay;
        Color attenuation;
        if (record.material->scatter(ray, record, attenuation, scatteredRay)) {
            return attenuation * computeRayColor(scatteredRay, world, depth - 1);
        } else {
            return Color(0, 0, 0);
        }
    }
    Vector3 unit = unitDirection(ray.direction);
    double t = 0.5 * (unit.y + 1.0);
    return ((1.0 - t) * Color(1.0, 1.0, 1.0)) + (t * Color(0.5, 0.75, 1.0));
}

}