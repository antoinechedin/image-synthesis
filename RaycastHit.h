#ifndef RAY_TRACING_RAYCASTHIT_H
#define RAY_TRACING_RAYCASTHIT_H


#include "Vec3.h"
#include "Ray.h"
#include "Material.h"
#include "AABB.h"

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

    virtual AABB boundingBox() const = 0;

    static bool xSort(Hittable *h1, Hittable *h2){
        return h1->boundingBox().min.x < h2->boundingBox().min.x;
    }

    static bool ySort(Hittable *h1, Hittable *h2){
        return h1->boundingBox().min.y < h2->boundingBox().min.y;
    }

    static bool zSort(Hittable *h1, Hittable *h2){
        return h1->boundingBox().min.z < h2->boundingBox().min.z;
    }
};


#endif //RAY_TRACING_RAYCASTHIT_H
