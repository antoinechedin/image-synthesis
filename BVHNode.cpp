//
// Created by antoine on 27/10/2019.
//

#include <algorithm>
#include <iostream>
#include "BVHNode.h"

BVHNode::BVHNode(std::vector<Hittable *> &list) {
    float xSize = box.max.x - box.min.x;
    float ySize = box.max.y - box.min.y;
    float zSize = box.max.z - box.min.z;

    bool xSplit = false, ySplit = false, zSplit = false;

    if (xSize > ySize) {
        if (xSize > zSize) { // x is the longest
            xSplit = true;
        } else { // z is the longest
            zSplit = true;
        }
    } else if (ySize > zSize) { // y is the longest
        ySplit = true;
    } else { // z is the longest
        zSplit = true;
    }

    if (xSplit) {
        std::sort(list.begin(), list.end(), Hittable::xSort);
    } else if (ySplit) {
        std::sort(list.begin(), list.end(), Hittable::ySort);
    } else {
        std::sort(list.begin(), list.end(), Hittable::zSort);
    }

    if (list.size() == 1)
        left = right = list[0];
    else if (list.size() == 2) {
        left = list[0];
        right = list[1];
    } else {
        std::vector<Hittable *> l, r;
        for (int i = 0; i < list.size(); ++i) {
            if (i <= list.size() / 2)
                l.push_back(list[i]);
            else
                r.push_back(list[i]);
        }
        left = new BVHNode(l);
        right = new BVHNode(r);
    }

    box = AABB::surroundingBox(left->boundingBox(), right->boundingBox());
}

bool BVHNode::hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit) const {
    if (box.hit(ray, minDist, maxDist)) {
        RaycastHit leftHit, rightHit;
        bool hasHitLeft = left->hit(ray, minDist, maxDist, leftHit);
        bool hasHitRight = right->hit(ray, minDist, maxDist, rightHit);
        if (hasHitLeft && hasHitRight) {
            if (leftHit.t < rightHit.t)
                raycastHit = leftHit;
            else
                raycastHit = rightHit;
            return true;
        } else if (hasHitLeft) {
            raycastHit = leftHit;
            return true;
        } else if (hasHitRight) {
            raycastHit = rightHit;
            return true;
        } else
            return false;
    } else return false;
}

AABB BVHNode::boundingBox() const {
    return box;
}
