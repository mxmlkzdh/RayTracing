#pragma once
#include <fstream>
#include <cmath>
#include "util.hpp"
#include "object.hpp"
#include "vector3.hpp"

namespace RayTracing {

// Write the translated [0,255] value of each color component.
void writePixel(std::ofstream& outputFile, const Color& color, const int samplesPerPixel) {
    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    const double r = std::sqrt(color.x / samplesPerPixel);
    const double g = std::sqrt(color.y / samplesPerPixel);
    const double b = std::sqrt(color.z / samplesPerPixel);
    outputFile
        << static_cast<int>(256 * Util::clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Util::clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Util::clamp(b, 0.0, 0.999)) << '\n';
}

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