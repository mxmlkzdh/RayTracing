// #include <spdlog/spdlog.h>
#include <argh/argh.h>
#include <iostream>
#include <fstream>
#include "util.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "sphere.hpp"

#define OUTPUT_FILE_PATH "data/output.ppm"

RayTracing::Color computeRayColor(const RayTracing::Ray& ray) {
    RayTracing::Sphere sphere(RayTracing::Point(0, 0, -1), 0.5);
    RayTracing::HitRecord record;
    if (sphere.hit(ray, 0, 100, record)) {
        return 0.5 * (record.normal + RayTracing::Color(1, 1, 1));
    }
    RayTracing::Vector3 unit = RayTracing::unitDirection(ray.direction);
    double t = 0.5 * (unit.y + 1.0);
    return ((1.0 - t) * RayTracing::Color(1.0, 1.0, 1.0)) + (t * RayTracing::Color(0.5, 0.75, 1.0));
}

int main(int argc, char const* argv[]) {

    // Automatically benchmarks the execution of this code block (main) in milli, micro, and nano seconds.
    RayTracing::Util::Timer timer;

    argh::parser cmdl = argh::parser(argc, argv);

    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    int width;
    cmdl({"-w", "--width"}, 400) >> width;
    const int IMAGE_WIDTH = width;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

    // Camera
    const double FOCAL_LENGTH = 1.0;
    const double VIEWPORT_WIDTH = 4.0;
    const double VIEWPORT_HEIGHT = VIEWPORT_WIDTH / ASPECT_RATIO;

    const RayTracing::Point ORIGIN = RayTracing::Point(0, 0, 0);
    const RayTracing::Vector3 HORIZONTAL = RayTracing::Vector3(VIEWPORT_WIDTH, 0, 0);
    const RayTracing::Vector3 VERTICAL = RayTracing::Vector3(0, VIEWPORT_HEIGHT, 0);
    const RayTracing::Vector3 LOWER_LEFT_CORNER = ORIGIN - (HORIZONTAL / 2) - (VERTICAL / 2) - RayTracing::Vector3(0, 0, FOCAL_LENGTH);

    // Render
    std::ofstream outputFile;
    outputFile.open(OUTPUT_FILE_PATH);
    if (outputFile.is_open()) {
        outputFile << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << '\n' << "255\n";
        std::cout << "Image Width: " << IMAGE_WIDTH << " | Image Height: " << IMAGE_HEIGHT << std::endl;
        for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
            std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < IMAGE_WIDTH; i++) {
                double u = static_cast<double>(i) / (IMAGE_WIDTH - 1);
                double v = static_cast<double>(j) / (IMAGE_HEIGHT - 1);
                RayTracing::Ray ray(ORIGIN, LOWER_LEFT_CORNER + (u * HORIZONTAL) + (v * VERTICAL) - ORIGIN);
                RayTracing::Color color = computeRayColor(ray);
                RayTracing::writePixel(outputFile, color);
            }
        }
    }
    std::cout << "\nDone!" << std::endl;
    outputFile.close();

    return EXIT_SUCCESS;

}
