//
// Created by antoine on 27/10/2019.
//

#include "AABB.h"

float AABB::ffmin(const float &a, const float &b) {
    return a < b ? a : b;
}

float AABB::ffmax(const float &a, const float &b) {
    return a > b ? a : b;
}

AABB::AABB() = default;

AABB::AABB(const Vec3 &min, const Vec3 &max) : min(min), max(max) {}

bool AABB::hit(const Ray &ray, float tmin, float tmax) const {
    float invD = 1.0f / ray.direction.x;
    float t0 = (min.x - ray.origin.x) * invD;
    float t1 = (max.x - ray.origin.x) * invD;
    if (invD < 0.0f)
        std::swap(t0, t1);
    tmin = t0 > tmin ? t0 : tmin;
    tmax = t1 < tmax ? t1 : tmax;
    if (tmax <= tmin)
        return false;

    invD = 1.0f / ray.direction.y;
    t0 = (min.y - ray.origin.y) * invD;
    t1 = (max.y - ray.origin.y) * invD;
    if (invD < 0.0f)
        std::swap(t0, t1);
    tmin = t0 > tmin ? t0 : tmin;
    tmax = t1 < tmax ? t1 : tmax;
    if (tmax <= tmin)
        return false;

    invD = 1.0f / ray.direction.z;
    t0 = (min.z - ray.origin.z) * invD;
    t1 = (max.z - ray.origin.z) * invD;
    if (invD < 0.0f)
        std::swap(t0, t1);
    tmin = t0 > tmin ? t0 : tmin;
    tmax = t1 < tmax ? t1 : tmax;
    if (tmax <= tmin)
        return false;

    return true;
}

AABB AABB::surroundingBox(const AABB &box1, const AABB &box2) {
    Vec3 min(ffmin(box1.min.x, box2.min.x),
             ffmin(box1.min.y, box2.min.y),
             ffmin(box1.min.z, box2.min.z));
    Vec3 max(ffmax(box1.max.x, box2.max.x),
             ffmax(box1.max.y, box2.max.y),
             ffmax(box1.max.z, box2.max.z));
    return AABB(min, max);

}
