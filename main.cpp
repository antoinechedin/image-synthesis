#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "Vec3.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Camera.h"
#include "BVHNode.h"
#include "Metadata.h"

Vec3 getColor(
        const Ray &ray,
        const Hittable &world,
        const int &maxDepth,
        std::default_random_engine &generator,
        Metadata &metadata
);

std::string timeFormat(const int &milliseconds) {
    std::stringstream ss;
    int milli = milliseconds;
    int sec = milli / 1000;
    milli %= 1000;
    int min = sec / 60;
    sec %= 60;
    int hour = min / 60;
    hour %= 60;

    ss << std::setw(2) << std::setfill('0') << hour << ":"
       << std::setw(2) << std::setfill('0') << min << ":"
       << std::setw(2) << std::setfill('0') << sec << "."
       << std::setw(3) << std::setfill('0') << milli;
    return ss.str();
}


int main() {
    std::ofstream file("picture.ppm");
    int width = 400;
    int height = 200;

    int numSample = 100;
    //int maxDepth = 50;

    std::vector<Hittable *> objects;
    objects.push_back(new Sphere(Vec3(2, 0, 0), 0.5, new Lambertian(Vec3(0.1, 0.9, 0.5))));
    objects.push_back(new Sphere(Vec3(1, 0, 0), 0.5, new Dielectric(Vec3(0.6, 0.8, 1), 1.5)));
//  objects.push_back(new Sphere(Vec3(1, 0, 0), -0.4, new Dielectric(1.5)));
    objects.push_back(new Sphere(Vec3(0, 0, 0), 0.5, new Lambertian(Vec3(0.5, 0.5, 0.5))));
    objects.push_back(new Sphere(Vec3(-1, 0, 0), 0.5, new Metal(Vec3(0.9, 0.8, 0.2), 0.3)));
    objects.push_back(new Sphere(Vec3(-2, 0, 0), 0.5, new Dielectric(Vec3(0.5, 1, 0.5), 1.5)));
    objects.push_back(new Sphere(Vec3(-2, 0, 0), -0.4, new Dielectric(Vec3(1, 1, 1), 1.5)));
    //objects.push_back(new Sphere(Vec3(0, -100.5, 0), 100, new Lambertian(Vec3(1.0, 0.2, 0.1))));

    HittableList world;
    world.objectList = objects;

    BVHNode bvh = BVHNode(objects);

    Camera camera = Camera(
            Vec3(0.5, 1, -2),
            Vec3(0, 0, 0),
            Vec3(0, 1, 0),
            60,
            float(width) / float(height),
            0.1,
            Vec3(0.5, 1, -2).norm()
    );
    std::default_random_engine randGenerator;
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    int progress = 0;
    Metadata metadata{0, 0};
    file << "P3\n" << width << " " << height << "\n255\n";

    auto start = std::chrono::high_resolution_clock::now();
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            Vec3 pixel = Vec3(0, 0, 0);
            for (int s = 0; s < numSample; ++s) {
                float u = (float(i) + dist(randGenerator)) / float(width);
                float v = (float(j) + dist(randGenerator)) / float(height);

                Ray ray = camera.getRay(u, v, randGenerator);
                pixel += getColor(ray, world, 0, randGenerator, metadata);
            }
            pixel /= float(numSample);

            int ir = int(255.99 * powf(pixel.x, 1.f / 2));
            int ig = int(255.99 * powf(pixel.y, 1.f / 2));
            int ib = int(255.99 * powf(pixel.z, 1.f / 2));
            file << ir << " " << ig << " " << ib << "\n";
        }

        ++progress;
        if (progress % (height / 100) == 0) {
            std::cout << "\rProgress: " << std::setw(3) << std::setfill('0')
                      << int(float(progress) / float(height) * 100) << "%" << std::flush;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "\rRender duration: " << timeFormat(duration.count()) << std::endl;
    std::cout << "Num Object hit: " << std::setw(12) << std::setfill(' ') << metadata.numHitObject << std::endl;
    std::cout << "Num BVH hit:    " << std::setw(12) << std::setfill(' ') << metadata.numHitBHV << std::endl;
    std::cout << "Total:          " << std::setw(12) << std::setfill(' ') << metadata.numHitBHV + metadata.numHitObject << std::endl;

    return EXIT_SUCCESS;
}

Vec3 getColor(
        const Ray &ray,
        const Hittable &world,
        const int &depth,
        std::default_random_engine &generator,
        Metadata &metadata
) {
    RaycastHit hit;
    if (world.hit(ray, 0.001f, std::numeric_limits<float>::max(), hit, metadata)) {
        Ray newRay;
        Vec3 attenuation;
        if (depth < 10 && hit.material->scatter(ray, hit, attenuation, newRay, generator)) {
            return attenuation * getColor(newRay, world, depth + 1, generator, metadata);
        } else {
            return Vec3(0, 0, 0);
        }

    } else {
        float t = 0.5f * (ray.direction.y + 1.0f);
        return (1.0f - t) * Vec3(1.0, 0.7, 0.7) + t * Vec3(0.5, 0.7, 1.0);
    }
}
