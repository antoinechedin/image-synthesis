#include <fstream>
#include <vector>
#include "Vec3.h"
#include "Ray.h"
#include "RaycastHit.h"
#include "Sphere.h"
#include "HittableList.h"

Vec3 getColor(const Ray &ray, const HittableList &world);

int main() {
    std::ofstream file("picture.ppm");
    int width = 600;
    int height = 300;

    HittableList world;
    world.objectList.push_back(new Sphere(Vec3(0, 0, 1), 0.5f));
    world.objectList.push_back(new Sphere(Vec3(0, -100.5f, 1), 100));

    Vec3 lower_left_corner(-2, -1, 1);
    Vec3 horizontal(4, 0, 0);
    Vec3 vertical(0, 2, 0);
    Vec3 origin(0, 0, 0);

    file << "P3\n" << width << " " << height << "\n255\n";
    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            if (j == 150 && i == 300)
                j = 150;

            float u = float(i) / float(width);
            float v = float(j) / float(height);

            Ray ray(origin, (lower_left_corner + u * horizontal + v * vertical).unit());
            Vec3 pixel = getColor(ray, world);

            int ir = int(255.99 * pixel.x);
            int ig = int(255.99 * pixel.y);
            int ib = int(255.99 * pixel.z);
            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    return EXIT_SUCCESS;
}

Vec3 getColor(const Ray &ray, const HittableList &world) {
    RaycastHit hit;
    if (world.hit(ray, 0.0f, std::numeric_limits<float>::max(), hit)) {
        return 0.5f * Vec3(hit.normal.x + 1, hit.normal.y + 1, hit.normal.z + 1);
    } else {
        float t = 0.5f * (ray.direction.y + 1.0f);
        return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
    }
}
