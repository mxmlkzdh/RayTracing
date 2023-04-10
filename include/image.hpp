#pragma once
#include <string>

namespace RayTracing {

class Image {
public:
    std::string fileName;
    int width;
    int height;
public:
    Image(const std::string& fileName, const int width, const int height):
        fileName(fileName), width(width), height(height) {
    }
    Image(const std::string& fileName, const int width, const double aspectRatio):
        fileName(fileName), width(width), height(static_cast<int>(width / aspectRatio)) {
    }
};

}