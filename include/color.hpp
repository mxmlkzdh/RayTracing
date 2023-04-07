#pragma once
#include <fstream>
#include "util.hpp"
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

}