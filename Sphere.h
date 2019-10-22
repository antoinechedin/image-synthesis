#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H


#include "RaycastHit.h"

class Sphere : public Hittable {
public:
    Vec3 center;
    float radius;
    Material *material;

    Sphere();

    ~Sphere() override;

    Sphere(const Vec3 &center, float radius, Material *material);
    
    bool hit(const Ray &ray, float minDist, float maxDist, RaycastHit &hit) const override;
};


#endif //RAY_TRACING_SPHERE_H
