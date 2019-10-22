#include <gtest/gtest.h>
#include <cmath>
#include "../Vec3.h"


TEST(Vec3, operators) {
    Vec3 v1(1, 2, 3);
    Vec3 v2(-2, 0, 1);
    Vec3 v3(1, -1, 0);
    ASSERT_EQ(v1, Vec3(1, 2, 3));
    ASSERT_EQ(v2, Vec3(-2, 0, 1));

    v1 += v2;
    v3 /= 2.0f;
    ASSERT_EQ(v1, Vec3(-1, 2, 4));
    ASSERT_EQ(v3, Vec3(0.5f, -0.5f, 0));
}

TEST(Vec3, dot) {
    Vec3 v1(1, 2, 3);
    Vec3 v2(-2, 0, 1);
    Vec3 v3(1, -1, 0);
    ASSERT_FLOAT_EQ(Vec3::dot(v1, v2), 1);
    ASSERT_FLOAT_EQ(Vec3::dot(v1, v3), -1);
    ASSERT_FLOAT_EQ(Vec3::dot(v2, v3), -2);
}

TEST(Vec3, cross) {
    Vec3 v1(1, 0, 0);
    Vec3 v2(0, 1, 0);
    Vec3 v3(0, 0, 1);
    ASSERT_EQ(Vec3::cross(v1, v2), v3);
    ASSERT_EQ(Vec3::cross(v2, v3), v1);
    ASSERT_EQ(Vec3::cross(v1, v3), -1 * v2);
}

TEST(Vec3, unit) {
    Vec3 v1(1, 2, 3);
    Vec3 v2(2, 2, 0);
    ASSERT_FLOAT_EQ(v1.unit().norm(), 1.0f);
    ASSERT_EQ(v2.unit(), Vec3(std::sqrt(2) / 2.0f, std::sqrt(2) / 2.0f, 0));
}
