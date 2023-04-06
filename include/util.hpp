#pragma once
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
inline double degreesToRadians(const double degrees) {
    return degrees * Constants::PI / 180.0;
}

}