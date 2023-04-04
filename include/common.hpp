#pragma once
#include <limits>
#include <random>

namespace RayTracing {

const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

double degreesToRadians(const double degrees) {
    return degrees * PI / 180.0;
}

double randomDouble() {
    // Returns a random real in [0,1).
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * randomDouble();
}

}