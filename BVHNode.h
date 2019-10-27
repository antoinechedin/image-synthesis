//
// Created by antoine on 27/10/2019.
//

#ifndef RAY_TRACING_BVHNODE_H
#define RAY_TRACING_BVHNODE_H


#include "RaycastHit.h"
#include "AABB.h"

class BVHNode : public Hittable{
public :
    Hittable *left;
    Hittable *right;
    AABB box;

    explicit BVHNode(std::vector<Hittable*> &list);

    bool hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit, Metadata &metadata) const override;

    AABB boundingBox() const override;
};


#endif //RAY_TRACING_BVHNODE_H
