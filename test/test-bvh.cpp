#include <gtest/gtest.h>
#include "../RaycastHit.h"
#include "../Sphere.h"
#include "../BVHNode.h"


TEST(BVH, constructor) {
    Material *m = new Lambertian(Vec3(1, 1, 1));
    std::vector<Hittable *> spheres;
    spheres.push_back(new Sphere(Vec3(1, 1, 0), 0.49, m));
    spheres.push_back(new Sphere(Vec3(2, 1, 0), 0.49, m));
    spheres.push_back(new Sphere(Vec3(3, 1, 0), 0.49, m));
    spheres.push_back(new Sphere(Vec3(3, 3, 0), 0.49, m));
    spheres.push_back(new Sphere(Vec3(7, 1, 0), 0.49, m));

    BVHNode bvh(spheres);
}

