// #include <spdlog/spdlog.h>
#include <argh/argh.h>
#include <iostream>
#include <fstream>
#include <memory>
#include "util.hpp"
#include "ray.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "constants.hpp"

#define OUTPUT_FILE_PATH "data/output.ppm"

RayTracing::Color computeRayColor(const RayTracing::Ray& ray, const RayTracing::World& world) {
    RayTracing::HitRecord record;
    if (world.hit(ray, 0, RayTracing::Constants::DOUBLE_INFINITY, record)) {
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
    int samples;
    cmdl({"-s", "--samples"}, 10) >> samples;
    const int SAMPLES_PER_PIXEL = samples;

    // World
    RayTracing::World world;
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0, 0, -1), 0.5));
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0, -100.5, -1), 100));

    // Camera
    RayTracing::Camera camera;

    // Render
    std::ofstream outputFile;
    outputFile.open(OUTPUT_FILE_PATH);
    if (outputFile.is_open()) {
        outputFile << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << '\n' << "255\n";
        std::cout << "Image Dimensions: " << IMAGE_WIDTH << " x " << IMAGE_HEIGHT << " | Samples Per Pixel: " << SAMPLES_PER_PIXEL << std::endl;
        for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
            std::cout << "\rProgress: " << 100 - static_cast<int>((static_cast<double>(j) / (IMAGE_HEIGHT - 1)) * 100) << "% "<< std::flush;
            for (int i = 0; i < IMAGE_WIDTH; i++) {
                RayTracing::Color color(0, 0, 0);
                for (int k = 0; k < SAMPLES_PER_PIXEL; k++) {
                    double u = (static_cast<double>(i) + RayTracing::Util::random()) / (IMAGE_WIDTH - 1);
                    double v = (static_cast<double>(j) + RayTracing::Util::random()) / (IMAGE_HEIGHT - 1);
                    RayTracing::Ray ray = camera.getRay(u, v);
                    color = color + computeRayColor(ray, world);
                }
                RayTracing::writePixel(outputFile, color, SAMPLES_PER_PIXEL);
            }
        }
    }
    std::cout << "\nDone!" << std::endl;
    outputFile.close();

    return EXIT_SUCCESS;

}
