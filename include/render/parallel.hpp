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

namespace RayTracing {

class ParallelRenderer: public Renderer {
public:
    std::size_t hardwareConcurrency;
public:
    ParallelRenderer(const std::size_t hardwareConcurrency): hardwareConcurrency(hardwareConcurrency) {}
    virtual void render(const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel, const int maxDepth) const override {
        int estimate = samplesPerPixel / static_cast<int>(hardwareConcurrency);
        int localSamplesPerPixel = samplesPerPixel % static_cast<int>(hardwareConcurrency) == 0 ? estimate : estimate + 1;
        std::vector<std::thread> threads;
        threads.reserve(hardwareConcurrency);
        for (std::size_t p = 0; p < hardwareConcurrency; p++) {
            threads.push_back(std::thread(renderTask, p, image, scene, camera, localSamplesPerPixel, maxDepth));
        }
        for (std::thread& thread : threads) {
            thread.join();
        }
        std::ofstream outputFile;
        outputFile.open(image.fileName);
        if (outputFile.is_open()) {
            outputFile << "P3\n" << image.width << ' ' << image.height << '\n' << "255\n";
            std::vector<std::ifstream> inputFiles(hardwareConcurrency);
            std::vector<std::string> fileNames(hardwareConcurrency);
            for (std::size_t p = 0; p < hardwareConcurrency; p++) {
                std::string localFileName = image.fileName + "_" + std::to_string(p);
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
    static void renderTask(const int id, const Image& image, const Scene& scene, const Camera& camera, const int samplesPerPixel, const int maxDepth) {
        std::string localFileName = image.fileName + "_" + std::to_string(id);
        std::ofstream outputFile(localFileName);
        if (outputFile.is_open()) {
            for (int j = image.height - 1; j >= 0; j--) {
                for (int i = 0; i < image.width; i++) {
                    Color color(0, 0, 0);
                    for (int k = 0; k < samplesPerPixel; k++) {
                        double u = (static_cast<double>(i) + Util::random()) / (image.width - 1);
                        double v = (static_cast<double>(j) + Util::random()) / (image.height - 1);
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