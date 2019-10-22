#include <gtest/gtest.h>
#include "../Vec3.h"


TEST(Vec3, dot) {
    Vec3 v1(1, 2, 3);
    Vec3 v2(-2, 0, 1);
    Vec3 v3(1, -1, 0);
    ASSERT_FLOAT_EQ(Vec3::dot(v1, v2), 1);
    ASSERT_FLOAT_EQ(Vec3::dot(v1, v3), -1);
    ASSERT_FLOAT_EQ(Vec3::dot(v2, v3), -2);
}

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
