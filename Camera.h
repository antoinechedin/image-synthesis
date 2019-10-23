#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H


#include <random>
#include "Vec3.h"
#include "Ray.h"

class Camera {
public:
    Vec3 u, v, w;
    float lensRadius;
    Vec3 origin;
    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;

    Camera(
            const Vec3 &origin,
            const Vec3 &lookAt,
            const Vec3 &up,
            const float &vfov,
            const float &aspect,
            const float &aperture,
            const float &focusDist
    );

    [[nodiscard]] Ray getRay(const float &u, const float &v, std::default_random_engine &generator) const;

    static Vec3 randomInUnitDisk(std::default_random_engine &generator);
};


#endif //RAY_TRACING_CAMERA_H
