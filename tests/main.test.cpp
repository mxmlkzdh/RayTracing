#include <gtest/gtest.h>
#include "vector3.hpp"
#include "ray.hpp"

TEST(Vector3, lengthEasy) {
    RayTracing::Vector3 v(-3, 0, 4);
    EXPECT_EQ(v.length(), 5.0);
}

TEST(Vector3, lengthComplex) {
    RayTracing::Vector3 v(2.5, 3.7, -4.91);
    EXPECT_EQ(v.length(), 6.6368742642903822);
}

TEST(Vector3, addition) {
    RayTracing::Vector3 v1(-3, 1, 4);
    RayTracing::Vector3 v2(2, 11, -14);
    RayTracing::Vector3 v3(-1, 12, -10);
    EXPECT_TRUE(v1 + v2 == v3);
}

TEST(Vector3, subtraction) {
    RayTracing::Vector3 v1(-3, 1, 4);
    RayTracing::Vector3 v2(2, 11, -14);
    RayTracing::Vector3 v3(-5, -10, 18);
    EXPECT_TRUE(v1 - v2 == v3);
}

TEST(Vector3, negative) {
    RayTracing::Vector3 v1(-3, 1, 4);
    RayTracing::Vector3 v2(3, -1, -4);
    EXPECT_TRUE(-v1 == v2);
}

TEST(Vector3, scalarProduct) {
    RayTracing::Vector3 v1(-3, 1, 4);
    RayTracing::Vector3 v2(6, -2, -8);
    EXPECT_TRUE(-2 * v1 == v2);
}

TEST(Vector3, scalarDivision) {
    RayTracing::Vector3 v1(-3, 1, 4);
    RayTracing::Vector3 v2(-3.0 / 2, 1.0 / 2, 2);
    EXPECT_TRUE(v1 / 2 == v2);
}

TEST(Vector3, dotProduct) {
    RayTracing::Vector3 v1(-3, 1, 4);
    RayTracing::Vector3 v2(6, 7, 0);
    EXPECT_TRUE(RayTracing::dot(v1, v2) == -11);
}

TEST(Vector3, crossProduct) {
    RayTracing::Vector3 v1(-3, 1.2, 4);
    RayTracing::Vector3 v2(1, 2, 3.5);
    RayTracing::Vector3 v3(-3.8, 14.5, -7.2);
    EXPECT_TRUE(RayTracing::cross(v1, v2) == v3);
}

TEST(Vector3, unitVector) {
    RayTracing::Vector3 v1(-3.0, 0, 4.0);
    RayTracing::Vector3 v2(-3.0 / 5.0, 0, 4.0 / 5.0);
    EXPECT_TRUE(RayTracing::unitVector(v1) == v2);
}

TEST(Ray, at) {
    RayTracing::Point origin(-3.0, 10, 41.0);
    RayTracing::Vector3 direction(1.5, 5.0, 4.0);
    RayTracing::Ray ray(origin, direction);
    RayTracing::Point p(-5.1, 3, 35.4);
    EXPECT_TRUE(ray.at(-1.4) == p);
}