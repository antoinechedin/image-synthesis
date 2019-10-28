#include <cmath>
#include "Sphere.h"

Sphere::Sphere() {
    this->center = Vec3(0.0f, 0.0f, 0.0f);
    this->radius = 0;
}

Sphere::~Sphere() {
    delete material;
}

Sphere::Sphere(const Vec3 &center, float radius, Material *material)
        : center(center), radius(radius), material(material) {}

bool Sphere::hit(const Ray &ray, float minDist, float maxDist, RaycastHit &hit, Metadata &metadata) const {
    ++metadata.numHitObject;

    Vec3 oc = ray.origin - center;
    float a = 1.0f; // Vec3::dot(ray.direction, ray.direction); Always 1 if direction is normalized
    float b = 2.0f * Vec3::dot(oc, ray.direction);
    float c = Vec3::dot(oc, oc) - radius * radius;

    float delta = b * b - 4 * a * c;
    if (delta > 0) {
        float t = (-b - std::sqrt(delta)) / (2 * a);
        if (t < maxDist && t > minDist) {
            hit.t = t;
            hit.point = ray.pointAt(t);
            hit.normal = (hit.point - center).unit();
            hit.material = material;
            return true;
        }
        t = (-b + std::sqrt(delta)) / (2 * a);
        if (t < maxDist && t > minDist) {
            hit.t = t;
            hit.point = ray.pointAt(t);
            hit.normal = (hit.point - center) / radius;
            hit.material = material;
            return true;
        }
    }
    return false;
}

AABB Sphere::boundingBox() const {
    return AABB(
            center - Vec3(radius, radius, radius),
            center + Vec3(radius, radius, radius)
    );
}
