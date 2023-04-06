// #include <spdlog/spdlog.h>
#include <iostream>
#include <fstream>
#include "util.hpp"
#include "color.hpp"

#define OUTPUT_FILE_PATH "data/output.ppm"

int main(int, char const**) {

    RayTracing::Util::Timer timer;

    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 800;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

    // Render
    std::ofstream outputFile;
    outputFile.open(OUTPUT_FILE_PATH);
    if (outputFile.is_open()) {
        outputFile << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << '\n' << "255\n";
        std::cout << "Image Width: " << IMAGE_WIDTH << " | Image Height: " << IMAGE_HEIGHT << std::endl;
        for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {
            std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < IMAGE_WIDTH; i++) {
                RayTracing::Color color(
                    static_cast<double>(i) / (IMAGE_WIDTH - 1),
                    static_cast<double>(j) / (IMAGE_HEIGHT - 1),
                    0.25
                );
                RayTracing::writePixel(outputFile, color);
            }
        }
    }
    std::cout << "\nDone!" << std::endl;
    outputFile.close();

    return EXIT_SUCCESS;

}
