#pragma once
#include <fstream>
#include "common.hpp"
#include "vector3d.hpp"

namespace RayTracing {

// Write the translated [0,255] value of each color component.
void writeColor(std::ofstream& outputFile, const Color& pixelColor, const int samplesPerPixel) {
    double r = pixelColor.x;
    double g = pixelColor.y;
    double b = pixelColor.z;
    // Divide the color by the number of samples.
    const double scale = 1.0 / samplesPerPixel;
    r = std::sqrt(r * scale);
    g = std::sqrt(g * scale);
    b = std::sqrt(b * scale);
    outputFile << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

}