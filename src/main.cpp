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
#include "lambertian.hpp"
#include "metal.hpp"

#define OUTPUT_FILE_PATH "data/output.ppm"

int main(int argc, char const* argv[]) {

    // Automatically benchmarks the execution of this code block (main) in seconds.
    RayTracing::Util::Timer timer;

    // Command line arguments parser
    argh::parser cmdl = argh::parser(argc, argv);

    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    int width;
    if (cmdl[{"-h"}]) { // For Full HD Resolution in 16/9 Aspect Ratio
        width = 1920;
    } else {
        cmdl({"-w", "--width"}, 400) >> width;
    }
    const int IMAGE_WIDTH = width;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
    int samples;
    cmdl({"-s", "--samples"}, 10) >> samples;
    const int SAMPLES_PER_PIXEL = samples;
    const int MAX_DEPTH = 50;

    // World
    RayTracing::World world;
    auto materialGround = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(0.5, 0.5, 0.5));
    auto materialCenter = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(0.0, 0.1, 0.3));
    auto materialLeft = std::make_shared<RayTracing::Metal>(RayTracing::Color(0.5, 0.5, 0.5));
    auto materialRight = std::make_shared<RayTracing::Metal>(RayTracing::Color(0.75, 0.5, 0.25));
    auto materialFront = std::make_shared<RayTracing::Metal>(RayTracing::Color(0.75, 0.0, 0.0));
    auto materialFrontFront = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(0.75, 0.5, 0.25));
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0, -100.5, -1), 100, materialGround));
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(0, 0, -1.35), 0.5, materialCenter));
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(-1.0, 0.0, -1), 0.5, materialLeft));
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(1.05, 0.0, -0.75), 0.5, materialRight));
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(-0.5, -0.38, -0.5), 0.12, materialFront));
    world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point(-0.75, -0.45, -0.5), 0.05, materialFrontFront));

    // Camera
    RayTracing::Camera camera(RayTracing::Point(0, 0.55, 1), RayTracing::Point(0, 0, -1.35), RayTracing::Vector3(0, 1, 0), 65.0, ASPECT_RATIO);

    // Render
    std::ofstream outputFile;
    outputFile.open(OUTPUT_FILE_PATH);
    if (outputFile.is_open()) {
        outputFile << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << '\n' << "255\n";
        std::cout << "Image Dimensions: " << IMAGE_WIDTH << " x " << IMAGE_HEIGHT << " | Samples Per Pixel: " << SAMPLES_PER_PIXEL << std::endl;
        for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
            std::cout << "\rProgress: " << 100 - static_cast<int>((static_cast<double>(j) / (IMAGE_HEIGHT - 1)) * 100) << "% " << std::flush;
            for (int i = 0; i < IMAGE_WIDTH; i++) {
                RayTracing::Color color(0, 0, 0);
                for (int k = 0; k < SAMPLES_PER_PIXEL; k++) {
                    double u = (static_cast<double>(i) + RayTracing::Util::random()) / (IMAGE_WIDTH - 1);
                    double v = (static_cast<double>(j) + RayTracing::Util::random()) / (IMAGE_HEIGHT - 1);
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
