#pragma once
#include <fstream>
#include "vector3.hpp"

namespace RayTracing {

// Write the translated [0,255] value of each color component.
void writePixel(std::ofstream& outputFile, const Color& color) {
    outputFile
        << static_cast<int>(255.999 * color.x) << ' '
        << static_cast<int>(255.999 * color.y) << ' '
        << static_cast<int>(255.999 * color.z) << '\n';
}

}