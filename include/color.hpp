#pragma once
#include <fstream>
#include "vector3.hpp"

namespace RayTracing {

// Write the translated [0,255] value of each color component.
void writeColor(std::ofstream& outputFile, const RayTracing::Color& pixelColor) {
    outputFile << static_cast<int>(255.999 * pixelColor.x) << ' '
        << static_cast<int>(255.999 * pixelColor.y) << ' '
        << static_cast<int>(255.999 * pixelColor.z) << '\n';
}

}