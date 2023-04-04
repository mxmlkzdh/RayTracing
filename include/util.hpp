#pragma once
#include <chrono>
#include <iostream>

namespace RayTracing::Util {

// Automatically benchmarks the execution of a code block in milli, micro, and nano seconds.
struct Timer final {
private:
    std::chrono::high_resolution_clock::time_point mStart;
public:
    Timer() { mStart = std::chrono::high_resolution_clock::now(); }
    ~Timer() {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        long long millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - mStart).count();
        long long micros = std::chrono::duration_cast<std::chrono::microseconds>(end - mStart).count();
        long long nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(end - mStart).count();
        std::cout << "(" << millis << " ms, " << micros << " μs, " << nanos << " ns)" << std::endl;
    }
};

}
