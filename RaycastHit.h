#ifndef RAY_TRACING_RAYCASTHIT_H
#define RAY_TRACING_RAYCASTHIT_H


#include "Vec3.h"
#include "Ray.h"

struct RaycastHit {
    float t;
    Vec3 point;
    Vec3 normal;
};

class Hittable {
public:
    virtual bool hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit) const = 0;
};


#endif //RAY_TRACING_RAYCASTHIT_H
