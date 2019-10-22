//
// Created by achedin on 22/10/2019.
//

#include "Camera.h"

Camera::Camera() {
    lowerLeftCorner = Vec3(-2, -1,1);
    horizontal = Vec3(4,0,0);
    vertical = Vec3(0,2,0);
    origin = Vec3(0,0,0);
}

Ray Camera::getRay(const float &u, const float &v) const {
    return Ray(origin, (lowerLeftCorner + u * horizontal + v * vertical - origin).unit());
}
