#pragma once
#include <fstream>
#include "util.hpp"
#include "object.hpp"
#include "vector3.hpp"

namespace RayTracing {

// Write the translated [0,255] value of each color component.
void writePixel(std::ofstream& outputFile, const Color& color, const int samplesPerPixel) {
    const double r = color.x / samplesPerPixel;
    const double g = color.y / samplesPerPixel;
    const double b = color.z / samplesPerPixel;
    outputFile
        << static_cast<int>(256 * Util::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Util::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Util::clamp(b, 0.0, 0.999)) << '\n';
}

Color computeRayColor(const Ray& ray, const Object& object, const int depth) {
    if (depth == 0) {
        return Color(0, 0, 0);
    }
    HitRecord record;
    if (object.hit(ray, 0, Constants::DOUBLE_INFINITY, record)) {
        Vector3 randomDirection = record.point + record.normal + randomInUnitSphere();
        Ray reflectionRay(record.point, randomDirection - record.point);
        return 0.5 * computeRayColor(reflectionRay, object, depth - 1);
    }
    Vector3 unit = unitDirection(ray.direction);
    double t = 0.5 * (unit.y + 1.0);
    return ((1.0 - t) * Color(1.0, 1.0, 1.0)) + (t * Color(0.5, 0.75, 1.0));
}

}