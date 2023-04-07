#pragma once
#include <random>
#include <chrono>
#include <iostream>
#include "constants.hpp"

namespace RayTracing::Util {

// Automatically benchmarks the execution of a code block in milli, micro, and nano seconds.
struct Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
public:
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        long long millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        long long micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        long long nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "(" << millis << " ms, " << micros << " μs, " << nanos << " ns)" << std::endl;
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
    return min + (max - min) * random();
}

inline double degreesToRadians(const double degrees) {
    return degrees * Constants::PI / 180.0;
}

}