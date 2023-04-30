#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <atomic>
#include "../image.hpp"
#include "../scene.hpp"
#include "../camera.hpp"
#include "../renderer.hpp"
#include "../util.hpp"
#include "../ray.hpp"
#include "../vector3.hpp"

#define BUILD_DIRECTORY "build/"

namespace RayTracing {
class ParallelRenderer: public Renderer {
public:
    std::size_t hardwareConcurrency;
public:
    ParallelRenderer(const std::size_t hardwareConcurrency): hardwareConcurrency(hardwareConcurrency) {}
    void render(const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel, const int maxDepth) const override {
        int estimate = samplesPerPixel / static_cast<int>(hardwareConcurrency);
        int localSamplesPerPixel = samplesPerPixel % static_cast<int>(hardwareConcurrency) == 0 ? estimate : estimate + 1;
        std::vector<std::thread> threads;
        threads.reserve(hardwareConcurrency);
        for (std::size_t p = 0; p < hardwareConcurrency - 1; p++) {
            threads.push_back(std::thread(renderTask, p, image, scene, camera, localSamplesPerPixel, hardwareConcurrency, maxDepth, false));
        }
        renderTask(hardwareConcurrency - 1, image, scene, camera, localSamplesPerPixel, hardwareConcurrency, maxDepth, true); // Run one instance on the main thread to show progress!
        for (std::thread& thread : threads) {
            thread.join();
        }
        std::cout << "\nProcessing ...";
        std::ofstream outputFile;
        outputFile.open(image.fileName);
        if (outputFile.is_open()) {
            outputFile << "P3\n" << image.width << ' ' << image.height << "\n255\n";
            std::vector<std::ifstream> inputFiles(hardwareConcurrency);
            std::vector<std::string> fileNames(hardwareConcurrency);
            for (std::size_t p = 0; p < hardwareConcurrency; p++) {
                std::string localFileName = std::string(BUILD_DIRECTORY) + "raw." + std::to_string(p);
                inputFiles[p] = std::ifstream(localFileName, std::ifstream::binary);
                fileNames[p] = localFileName;
            }
            for (int j = image.height - 1; j >= 0; j--) {
                for (int i = 0; i < image.width; i++) {
                    Color color(0, 0, 0);
                    for (std::size_t p = 0; p < hardwareConcurrency; p++) {
                        Color temp;
                        inputFiles[p].read(reinterpret_cast<char*>(&temp), sizeof(Color));
                        color = color + temp;
                    }
                    writePixel(outputFile, color, samplesPerPixel);
                }
            }
            for (std::size_t p = 0; p < hardwareConcurrency; p++) {
                inputFiles[p].close();
                std::remove(fileNames[p].c_str());
            }
        }
        outputFile.close();
    }
private:
    static void renderTask(const int id, const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel, const std::size_t hardwareConcurrency, const int maxDepth, const bool showProgress) {
        std::string localFileName = std::string(BUILD_DIRECTORY) + "raw." + std::to_string(id);
        std::ofstream outputFile(localFileName);
        if (outputFile.is_open()) {
            if (showProgress) {
                std::cout << "Image Dimensions: " << image.width << " x " << image.height << " | Samples Per Pixel: "
                    << samplesPerPixel * static_cast<int>(hardwareConcurrency) << " | Running on " << hardwareConcurrency << " threads" << std::endl;
            }
            for (int j = image.height - 1; j >= 0; j--) {
                if (showProgress) {
                    std::cout << "\rProgress: " << 100 - static_cast<int>((static_cast<double>(j) / (image.height - 1)) * 100) << "% " << std::flush;
                }
                for (int i = 0; i < image.width; i++) {
                    Color color(0, 0, 0);
                    for (int k = 0; k < samplesPerPixel; k++) {
                        double u = (i + Util::random()) / (image.width - 1);
                        double v = (j + Util::random()) / (image.height - 1);
                        Ray ray = camera.getRay(u, v);
                        color = color + computeRayColor(ray, scene.world, scene.backgroundColor, maxDepth);
                    }
                    outputFile.write(reinterpret_cast<char*>(&color), sizeof(Color));
                }
            }
        }
        outputFile.close();
    }
};

}