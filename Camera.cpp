//
// Created by achedin on 22/10/2019.
//

#include <math.h>
#include <iostream>
#include "Camera.h"

Camera::Camera(const Vec3 &origin, const Vec3 &lookAt, const Vec3 &up, const float &vfov, const float &aspect) {
    Vec3 u, v, w;
    float theta = vfov * float(M_PI) / 180;
    float halfHeight = tanf(theta / 2);
    float halfWidth = aspect * halfHeight;
    this->origin = origin;
    w = (origin - lookAt).unit();
    u = Vec3::cross(w, up).unit();
    v = Vec3::cross(u, w);
    lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
    horizontal = 2 * halfWidth * u;
    vertical = 2 * halfHeight * v;

}

Ray Camera::getRay(const float &u, const float &v) const {
    return Ray(origin, (lowerLeftCorner + u * horizontal + v * vertical - origin).unit());
}
