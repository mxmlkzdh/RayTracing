#pragma once
#include <iostream>
#include <fstream>
#include "../image.hpp"
#include "../scene.hpp"
#include "../camera.hpp"
#include "../renderer.hpp"
#include "../util.hpp"
#include "../ray.hpp"
#include "../vector3.hpp"

namespace RayTracing {

class LinearRenderer: public Renderer {
public:
    virtual void render(const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel, const int maxDepth) const override {
        Color bgColor(0, 0, 0);
        std::ofstream outputFile(image.fileName);
        if (outputFile.is_open()) {
            std::cout << "Image Dimensions: " << image.width << " x " << image.height << " | Samples Per Pixel: " << samplesPerPixel << std::endl;
            outputFile << "P3\n" << image.width << ' ' << image.height << '\n' << "255\n";
            for (int j = image.height - 1; j >= 0; j--) {
                std::cout << "\rProgress: " << 100 - static_cast<int>((static_cast<double>(j) / (image.height - 1)) * 100) << "% " << std::flush;
                for (int i = 0; i < image.width; i++) {
                    Color color(0, 0, 0);
                    for (int k = 0; k < samplesPerPixel; k++) {
                        double u = (static_cast<double>(i) + Util::random()) / (image.width - 1);
                        double v = (static_cast<double>(j) + Util::random()) / (image.height - 1);
                        Ray ray = camera.getRay(u, v);
                        color = color + computeRayColor(ray, scene.world, bgColor, maxDepth);
                    }
                    writePixel(outputFile, color, samplesPerPixel);
                }
            }
        }
        outputFile.close();
    }
};

}