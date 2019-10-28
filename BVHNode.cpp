//
// Created by antoine on 27/10/2019.
//

#include <algorithm>
#include <iostream>
#include "BVHNode.h"

BVHNode::BVHNode(std::vector<Hittable *> &list) {
    if(!list.empty()){
        this->box = list[0]->boundingBox();
        for (size_t i = 1; i < list.size(); ++i) {
            this->box = AABB::surroundingBox(box, list[i]->boundingBox());
        }
    }

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
}

bool BVHNode::hit(const Ray &ray, float minDist, float maxDist, RaycastHit &raycastHit, Metadata &metadata) const {
    ++metadata.numHitBHV;

    if (box.hit(ray, minDist, maxDist)) {
        RaycastHit leftHit, rightHit;
        bool hasHitLeft = left->hit(ray, minDist, maxDist, leftHit, metadata);
        bool hasHitRight = right->hit(ray, minDist, maxDist, rightHit, metadata);
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
