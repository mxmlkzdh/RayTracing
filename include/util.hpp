#pragma once
#include <random>
#include <chrono>
#include <iostream>
#include "constants.hpp"

namespace RayTracing::Util {

// Automatically benchmarks the execution of a code block in seconds.
struct Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
public:
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        long long s = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
        if (s >= 60) {
            long long m = s / 60;
            s %= 60;
            std::cout << "\nRender Time: " << m << " minutes and " << s << " seconds" << std::endl;
        } else {
            std::cout << "\nRender Time: " << s << " seconds" << std::endl;
        }
    }
};

// Utility Functions

// Returns a random double in [0,1).
inline double random() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// Returns a random double in [min,max).
inline double random(const double min, const double max) {
    if (max == min) return min;
    return min + (max - min) * random();
}

inline double degreesToRadians(const double degrees) {
    return degrees * Constants::PI / 180.0;
}

inline double clamp(const double x, const double min, const double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

}