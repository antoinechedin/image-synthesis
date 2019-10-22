#ifndef RAY_TRACING_RAYCASTHIT_H
#define RAY_TRACING_RAYCASTHIT_H


#include "Vec3.h"
#include "Ray.h"
#include "Material.h"

class Material;

struct RaycastHit {
    float t = 0.0f;
    Vec3 point;
    Vec3 normal;
    Material *material;
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit) const = 0;
};


#endif //RAY_TRACING_RAYCASTHIT_H
