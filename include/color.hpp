#pragma once
#include <fstream>
#include <cmath>
#include "util.hpp"
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

}