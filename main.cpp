#include <fstream>
#include <vector>
#include <random>
#include "Vec3.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"

Vec3 getColor(const Ray &ray, const HittableList &world, const int &maxDepth, std::default_random_engine &generator);


int main() {
    std::ofstream file("picture.ppm");
    int width = 400;
    int height = 200;

    int numSample = 100;
    int maxDepth = 20;

    HittableList world;
    world.objectList.push_back(new Sphere(Vec3(0, 0, 1), 0.5f, new Lambertian(Vec3(0.1f, 0.2f, 0.5f))));
    world.objectList.push_back(new Sphere(Vec3(0, -100.5f, 1), 100, new Lambertian(Vec3(0.8f, 0.8f, 0.0f))));
    world.objectList.push_back(new Sphere(Vec3(1, 0, 1), 0.5f, new Metal(Vec3(0.8f, 0.6f, 0.2f), 1)));
    world.objectList.push_back(new Sphere(Vec3(-1, 0, 1), 0.5f, new Dielectric(1.5f)));
    world.objectList.push_back(new Sphere(Vec3(-1, 0, 1), -0.45f, new Dielectric(1.5f)));

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
                pixel += getColor(ray, world, 0, randGen);
            }
            pixel /= float(numSample);

            int ir = int(255.99 * powf(pixel.x, 1.f / 2.2f));
            int ig = int(255.99 * powf(pixel.y, 1.f / 2.2f));
            int ib = int(255.99 * powf(pixel.z, 1.f / 2.2f));
            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    return EXIT_SUCCESS;
}

Vec3 getColor(const Ray &ray, const HittableList &world, const int &depth, std::default_random_engine &generator) {
    RaycastHit hit;
    if (world.hit(ray, 0.001f, std::numeric_limits<float>::max(), hit)) {
        Ray newRay;
        Vec3 attenuation;
        if (depth < 50 && hit.material->scatter(ray, hit, attenuation, newRay, generator)) {
            return attenuation * getColor(newRay, world, depth + 1, generator);
        } else {
            return Vec3(0, 0, 0);
        }

    } else {
        float t = 0.5f * (ray.direction.y + 1.0f);
        return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
    }
}
