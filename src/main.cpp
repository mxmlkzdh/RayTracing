// #include <spdlog/spdlog.h>
// #include <argh/argh.h>
#include <iostream>
#include <fstream>
#include "util.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "constants.hpp"
#include "engine.hpp"
#include "scene.hpp"
#include "image.hpp"
#include "geometry/world.hpp"

#define DEFAULT_OUTPUT_FILE_PATH "data/output.ppm"

int main(int, char const**) {

    // Automatically benchmarks the execution of this code block (main) in seconds.
    RayTracing::Util::Timer timer;

    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const RayTracing::Image image(DEFAULT_OUTPUT_FILE_PATH, 1200, ASPECT_RATIO);

    // World
    RayTracing::World world = RayTracing::Scene().getWorld();

    // Camera
    const RayTracing::Point lookFrom(0, 0, 1.5);
    const RayTracing::Point lookAt(0, 0, -1.35);
    const RayTracing::Vector3 vUp(0, 1, 0);
    const double vFoV = 45.0;
    RayTracing::Camera camera(lookFrom, lookAt, vUp, vFoV, ASPECT_RATIO);

    // Render
    const int SAMPLES_PER_PIXEL = 10;
    const int MAX_DEPTH = 50;

    std::ofstream outputFile;
    outputFile.open(image.fileName);
    if (outputFile.is_open()) {
        outputFile << "P3\n" << image.width << ' ' << image.height << '\n' << "255\n";
        std::cout << "Image Dimensions: " << image.width << " x " << image.height << " | Samples Per Pixel: " << SAMPLES_PER_PIXEL << std::endl;
        for (int j = image.height - 1; j >= 0; j--) {
            std::cout << "\rProgress: " << 100 - static_cast<int>((static_cast<double>(j) / (image.height - 1)) * 100) << "% " << std::flush;
            for (int i = 0; i < image.width; i++) {
                RayTracing::Color color(0, 0, 0);
                for (int k = 0; k < SAMPLES_PER_PIXEL; k++) {
                    double u = (static_cast<double>(i) + RayTracing::Util::random()) / (image.width - 1);
                    double v = (static_cast<double>(j) + RayTracing::Util::random()) / (image.height - 1);
                    RayTracing::Ray ray = camera.getRay(u, v);
                    color = color + RayTracing::computeRayColor(ray, world, MAX_DEPTH);
                }
                RayTracing::writePixel(outputFile, color, SAMPLES_PER_PIXEL);
            }
        }
    }
    outputFile.close();

    return EXIT_SUCCESS;

}
