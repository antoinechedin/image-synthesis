#ifndef RAY_TRACING_HITTABLELIST_H
#define RAY_TRACING_HITTABLELIST_H


#include <vector>
#include "RaycastHit.h"

class HittableList: public Hittable{
public:
    std::vector<Hittable*> objectList;

    ~HittableList();

    bool hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit) const override;
};


#endif //RAY_TRACING_HITTABLELIST_H
