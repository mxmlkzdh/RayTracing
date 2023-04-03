#include <gtest/gtest.h>
#include "vector3.hpp"

using namespace RayTracing;

TEST(Vector3, lengthEasy) {
    Vector3 v(-3, 0, 4);
    EXPECT_EQ(v.length(), 5.0);
}

TEST(Vector3, lengthComplex) {
    Vector3 v(2.5, 3.7, -4.91);
    EXPECT_EQ(v.length(), 6.6368742642903822);
}

TEST(Vector3, addition) {
    Vector3 v1(-3, 1, 4);
    Vector3 v2(2, 11, -14);
    Vector3 v3(-1, 12, -10);
    EXPECT_TRUE(v1 + v2 == v3);
}

TEST(Vector3, subtraction) {
    Vector3 v1(-3, 1, 4);
    Vector3 v2(2, 11, -14);
    Vector3 v3(-5, -10, 18);
    EXPECT_TRUE(v1 - v2 == v3);
}

TEST(Vector3, negative) {
    Vector3 v1(-3, 1, 4);
    Vector3 v2(3, -1, -4);
    EXPECT_TRUE(-v1 == v2);
}

TEST(Vector3, scalarProduct) {
    Vector3 v1(-3, 1, 4);
    Vector3 v2(6, -2, -8);
    EXPECT_TRUE(-2 * v1 == v2);
}

TEST(Vector3, scalarDivision) {
    Vector3 v1(-3, 1, 4);
    Vector3 v2(-3.0 / 2, 1.0 / 2, 2);
    EXPECT_TRUE(v1 / 2 == v2);
}

TEST(Vector3, dotProduct) {
    Vector3 v1(-3, 1, 4);
    Vector3 v2(6, 7, 0);
    EXPECT_TRUE(dot(v1, v2) == -11);
}

TEST(Vector3, crossProduct) {
    Vector3 v1(-3, 1.2, 4);
    Vector3 v2(1, 2, 3.5);
    Vector3 v3(-3.8, 14.5, -7.2);
    EXPECT_TRUE(cross(v1, v2) == v3);
}

TEST(Vector3, unitVector) {
    Vector3 v1(-3.0, 0, 4.0);
    Vector3 v2(-3.0 / 5.0, 0, 4.0 / 5.0);
    EXPECT_TRUE(unit(v1) == v2);
}