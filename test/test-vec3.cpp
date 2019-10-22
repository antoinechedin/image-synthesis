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
