//
// Created by achedin on 22/10/2019.
//

#include <math.h>
#include <iostream>
#include "Camera.h"

Camera::Camera(
        const Vec3 &origin,
        const Vec3 &lookAt,
        const Vec3 &up,
        const float &vfov,
        const float &aspect,
        const float &aperture,
        const float &focusDist
) {
    this->origin = origin;
    w = (origin - lookAt).unit();
    u = Vec3::cross(w, up).unit();
    v = Vec3::cross(u, w);
    lensRadius = aperture /2.0f;

    float theta = vfov * float(M_PI) / 180;
    float halfHeight = tanf(theta / 2);
    float halfWidth = aspect * halfHeight;


    lowerLeftCorner = origin
                      - halfWidth * focusDist * u
                      - halfHeight * focusDist * v
                      - focusDist * w;
    horizontal = 2 * halfWidth * focusDist * u;
    vertical = 2 * halfHeight * focusDist * v;
}

Ray Camera::getRay(const float &s, const float &t, std::default_random_engine &generator) const {
    Vec3 rd = lensRadius * randomInUnitDisk(generator);
    Vec3 offset = u * rd.x + v * rd.y;
    return Ray(
            origin + offset,
            (lowerLeftCorner + s * horizontal + t * vertical - origin - offset).unit()
    );
}

Vec3 Camera::randomInUnitDisk(std::default_random_engine &generator) {
    Vec3 point;
    std::uniform_real_distribution dist(-0.5f, 0.5f);
    do {
        point = Vec3(dist(generator), dist(generator), 0);
    } while (point.squaredNorm() > 1.0);
    return point;
}
