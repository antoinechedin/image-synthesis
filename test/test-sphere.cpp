#include <gtest/gtest.h>
#include "../Vec3.h"
#include "../Ray.h"
#include "../Sphere.h"


TEST(Sphere, hit) {
    RaycastHit hit;

    Ray ray = Ray(Vec3(0, 0, 0), Vec3(0, 0, 1));
    Sphere sphere = Sphere(Vec3(0, 0, 2), 1);
    ASSERT_TRUE(sphere.hit(ray, 0, 100, hit));
    ASSERT_FLOAT_EQ(hit.t, 1.0f);

    sphere = Sphere(Vec3(0,0,-1), 10);
    ASSERT_TRUE(sphere.hit(ray, 0, 100, hit));
    ASSERT_FLOAT_EQ(hit.t, 9.0f);
}
