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
    virtual void render(const Image image, const Scene scene, const Camera camera, const int samplesPerPixel, const int maxDepth) const override {
        std::ofstream outputFile;
        outputFile.open(image.fileName);
        if (outputFile.is_open()) {
            outputFile << "P3\n" << image.width << ' ' << image.height << '\n' << "255\n";
            std::cout << "Image Dimensions: " << image.width << " x " << image.height << " | Samples Per Pixel: " << samplesPerPixel << std::endl;
            for (int j = image.height - 1; j >= 0; j--) {
                std::cout << "\rProgress: " << 100 - static_cast<int>((static_cast<double>(j) / (image.height - 1)) * 100) << "% " << std::flush;
                for (int i = 0; i < image.width; i++) {
                    Color color(0, 0, 0);
                    for (int k = 0; k < samplesPerPixel; k++) {
                        double u = (static_cast<double>(i) + Util::random()) / (image.width - 1);
                        double v = (static_cast<double>(j) + Util::random()) / (image.height - 1);
                        Ray ray = camera.getRay(u, v);
                        color = color + computeRayColor(ray, scene.world, maxDepth);
                    }
                    writePixel(outputFile, color, samplesPerPixel);
                }
            }
        }
        outputFile.close();
    }
    ~LinearRenderer() {}
private:
    // Write the translated [0,255] value of each color component.
    void writePixel(std::ofstream& outputFile, const Color& color, const int samplesPerPixel) const {
        // Divide the color by the number of samples and gamma-correct for gamma=2.0.
        const double r = std::sqrt(color.x / samplesPerPixel);
        const double g = std::sqrt(color.y / samplesPerPixel);
        const double b = std::sqrt(color.z / samplesPerPixel);
        outputFile
            << static_cast<int>(256 * Util::clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Util::clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * Util::clamp(b, 0.0, 0.999)) << '\n';
    }
    Color computeRayColor(const Ray& ray, const Object& world, const int depth) const {
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
};

}