#pragma once
#include <limits>

namespace RayTracing {

const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

double degreesToRadians(const double degrees) {
    return degrees * PI / 180.0;
}

}