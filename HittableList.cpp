#include "HittableList.h"

HittableList::~HittableList() {
    for (Hittable *object : objectList) {
        delete object;
    }
}

bool HittableList::hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit, Metadata &metadata) const {
    RaycastHit tempHit;
    bool hasHit = false;
    float currentDist = maxDist;

    for (Hittable *object : objectList) {
        if (object->hit(ray, minDist, currentDist, tempHit, metadata)) {
            hasHit = true;
            currentDist = tempHit.t;
            raycastHit = tempHit;
        }
    }
    return hasHit;
}

AABB HittableList::boundingBox() const {
    if (objectList.empty()) return AABB(Vec3(), Vec3());
    AABB box;
    for (Hittable *object : objectList) {
        box = AABB::surroundingBox(box, object->boundingBox());
    }
    return box;
}
