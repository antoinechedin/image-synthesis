#include "HittableList.h"

HittableList::~HittableList() {
    for (Hittable *object : objectList) {
        delete object;
    }
}

bool HittableList::hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit) const {
    RaycastHit tempHit;
    bool hasHit = false;
    float currentDist = maxDist;

    for (Hittable *object : objectList) {
        if (object->hit(ray, minDist, currentDist, tempHit)) {
            hasHit = true;
            currentDist = tempHit.t;
            raycastHit = tempHit;
        }
    }
    return hasHit;
}
