#pragma once
#include <fstream>
#include "util.hpp"
#include "image.hpp"
#include "scene.hpp"
#include "camera.hpp"

namespace RayTracing {

class Renderer {
public:
    virtual void render(const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel, const int maxDepth) const = 0;
    virtual ~Renderer() {}
};

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

Color computeRayColor(const Ray& ray, const Object& world, const Color& background, const int depth) {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth == 0) {
        return Color(0, 0, 0);
    }
    HitRecord record;
    if (!world.hit(ray, 0.001, Constants::DOUBLE_INFINITY, record)) {
        return background;
    }
    Ray scatteredRay;
    Color attenuation;
    Color emitted = record.material->emit(record.u, record.v, record.point);
    if (!record.material->scatter(ray, record, attenuation, scatteredRay)) {
        return emitted;
    }
    return emitted + attenuation * computeRayColor(scatteredRay, world, background, depth - 1);
}

}