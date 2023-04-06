#pragma once
#include <limits>
#include <random>

namespace RayTracing::Common {

// Constants
const double DOUBLE_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Functions
inline double degreesToRadians(const double degrees) {
    return degrees * PI / 180.0;
}

}
