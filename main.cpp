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

    int numSample = 1000;
    int maxDepth = 50;

    HittableList world;
    world.objectList.push_back(new Sphere(Vec3(2, 0, 0), 0.5, new Lambertian(Vec3(0.1, 0.9, 0.5))));
    world.objectList.push_back(new Sphere(Vec3(1, 0, 0), 0.5, new Dielectric(1.5)));
//    world.objectList.push_back(new Sphere(Vec3(1, 0, 0), -0.4, new Dielectric(1.5)));
    world.objectList.push_back(new Sphere(Vec3(0, 0, 0), 0.5, new Lambertian(Vec3(0.5, 0.5, 0.5))));
    world.objectList.push_back(new Sphere(Vec3(-1, 0, 0), 0.5, new Metal(Vec3(0.9, 0.8, 0.2), 0.3)));
    world.objectList.push_back(new Sphere(Vec3(-2, 0, 0), 0.5, new Lambertian(Vec3(0.1, 0.2, 0.1))));
    world.objectList.push_back(new Sphere(Vec3(0, -100.5, 0), 100, new Lambertian(Vec3(1.0, 0.2, 0.1))));


    Camera camera = Camera(
            Vec3(3, 1, -2),
            Vec3(0, 0, 0),
            Vec3(0, 1, 0),
            30,
            float(width) / float(height),
            0.3,
            Vec3(3, 1, -2).norm()
    );
    std::default_random_engine randGenerator;
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    file << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            Vec3 pixel = Vec3(0, 0, 0);
            for (int s = 0; s < numSample; ++s) {
                float u = (float(i) + dist(randGenerator)) / float(width);
                float v = (float(j) + dist(randGenerator)) / float(height);

                Ray ray = camera.getRay(u, v, randGenerator);
                pixel += getColor(ray, world, 0, randGenerator);
            }
            pixel /= float(numSample);

            int ir = int(255.99 * powf(pixel.x, 1.f / 2));
            int ig = int(255.99 * powf(pixel.y, 1.f / 2));
            int ib = int(255.99 * powf(pixel.z, 1.f / 2));
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
        return (1.0f - t) * Vec3(1.0, 0.7, 0.7) + t * Vec3(0.5, 0.7, 1.0);
    }
}
