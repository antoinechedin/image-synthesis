#include <cmath>
#include "Sphere.h"

Sphere::Sphere() {
    this->center = Vec3(0.0f, 0.0f, 0.0f);
    this->radius = 0;
}

Sphere::Sphere(const Vec3 &center, float radius) {
    this->center = center;
    this->radius = radius;
}

bool Sphere::hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit) const {
    Vec3 oc = ray.origin - center;
    float a = 1.0f; // Vec3::dot(ray.direction, ray.direction); Always 1 if direction is normalized
    float b = 2.0f * Vec3::dot(oc, ray.direction);
    float c = Vec3::dot(oc, oc) - radius * radius;

    float delta = b * b - 4 * a * c;
    if (delta > 0) {
        float t = (-b - std::sqrt(delta)) / (2 * a);
        if (t < maxDist && t > minDist) {
            raycastHit.t = t;
            raycastHit.point = ray.pointAt(t);
            raycastHit.normal = (raycastHit.point - center) / radius;
            return true;
        }
        t = (-b + std::sqrt(delta)) / (2 * a);
        if (t < maxDist && t > minDist) {
            raycastHit.t = t;
            raycastHit.point = ray.pointAt(t);
            raycastHit.normal = (raycastHit.point - center) / radius;
            return true;
        }
    }
    return false;
}
