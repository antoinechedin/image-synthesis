#ifndef RAY_TRACING_HITTABLELIST_H
#define RAY_TRACING_HITTABLELIST_H


#include <vector>
#include "RaycastHit.h"
#include "AABB.h"

class Hittable;

class HittableList: public Hittable{
public:
    std::vector<Hittable*> objectList;

    ~HittableList() override ;

    bool hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit, Metadata &metadata) const override;

    AABB boundingBox() const override;
};


#endif //RAY_TRACING_HITTABLELIST_H
