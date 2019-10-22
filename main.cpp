#include <fstream>
#include <vector>
#include <random>
#include "Vec3.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"

Vec3 getColor(const Ray &ray, const HittableList &world, std::default_random_engine &generator);

Vec3 randomDirInHemisphereCosWeight(const Vec3 normal, std::default_random_engine &generator);

int main() {
    std::ofstream file("picture.ppm");
    int width = 400;
    int height = 200;

    int numSample = 100;

    HittableList world;
    world.objectList.push_back(new Sphere(Vec3(0, 0, 1), 0.5f));
    world.objectList.push_back(new Sphere(Vec3(0, -100.5f, 1), 100));

    Camera camera = Camera();
    std::default_random_engine randGen;
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    file << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            Vec3 pixel = Vec3(0, 0, 0);
            for (int s = 0; s < numSample; ++s) {
                float u = (float(i) + dist(randGen)) / float(width);
                float v = (float(j) + dist(randGen)) / float(height);

                Ray ray = camera.getRay(u, v);
                pixel += getColor(ray, world, randGen);
            }
            pixel /= float(numSample);

            int ir = int(255.99 * powf(pixel.x, 1.f/2.2f));
            int ig = int(255.99 * powf(pixel.y, 1.f/2.2f));
            int ib = int(255.99 * powf(pixel.z, 1.f/2.2f));
            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    return EXIT_SUCCESS;
}

Vec3 getColor(const Ray &ray, const HittableList &world, std::default_random_engine &generator) {
    RaycastHit hit;
    if (world.hit(ray, 0.001f, std::numeric_limits<float>::max(), hit)) {
        Vec3 newDir = randomDirInHemisphereCosWeight(hit.normal, generator);
        return 0.5f * getColor(Ray(hit.point, newDir), world, generator) * 0.5f;
    } else {
        float t = 0.5f * (ray.direction.y + 1.0f);
        return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
    }
}

Vec3 randomDirInHemisphereCosWeight(const Vec3 normal, std::default_random_engine &generator) {
    std::uniform_real_distribution dist(0.0f, 1.0f);
    float r1 = dist(generator);
    float r2 = dist(generator);
    float x = cosf(2.0f * M_PI * r1) * sqrtf(1 - r2);
    float y = sinf(2.0f * M_PI * r1) * sqrtf(1 - r2);
    float z = sqrtf(r2);

    Vec3 bx(1, 2, 3);
    Vec3 by = Vec3::cross(normal, bx.unit()).unit();
    bx = Vec3::cross(by, normal).unit();
    return Vec3(x * bx + y * by + z * normal);
}
