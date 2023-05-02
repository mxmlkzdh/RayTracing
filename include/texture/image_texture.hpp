#pragma once
#include <iostream>
#include "../vector3.hpp"
#include "../util.hpp"
#include "../texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb/stb_image.h"

namespace RayTracing {

class ImageTexture: public Texture {
private:
    unsigned char* data;
    int width;
    int height;
    int bytesPerScanline;
    const static int BYTES_PER_PIXEL = 3;
public:
    ImageTexture(): data(nullptr), width(0), height(0), bytesPerScanline(0) {}
    ImageTexture(const char* filename) {
        int componentsPerPixel = BYTES_PER_PIXEL;
        data = stbi_load(filename, &width, &height, &componentsPerPixel, componentsPerPixel);
        if (!data) {
            std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
            width = height = 0;
        }
        bytesPerScanline = BYTES_PER_PIXEL * width;
    }
    ~ImageTexture() {
        delete data;
    }
    Color value(double u, double v, const Point&) const override {
        // If we have no texture data, then return solid cyan as a debugging aid.
        if (data == nullptr) {
            return Color(0, 1, 1);
        }
        // Clamp input texture coordinates to [0,1] x [1,0]
        u = Util::clamp(u, 0.0, 1.0);
        v = 1.0 - Util::clamp(v, 0.0, 1.0);  // Flip v to image coordinates.
        int i = static_cast<int>(u * width);
        int j = static_cast<int>(v * height);
        // Clamp integer mapping, since actual coordinates should be less than 1.0
        if (i >= width) {
            i = width - 1;
        }
        if (j >= height) {
            j = height - 1;
        }
        const double colorScale = 1.0 / 255.0;
        unsigned char* pixel = data + (j * bytesPerScanline) + (i * BYTES_PER_PIXEL);
        return Color(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
    }
};

}