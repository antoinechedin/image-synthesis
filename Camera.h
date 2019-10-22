#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H


#include "Vec3.h"
#include "Ray.h"

class Camera {
public:
    Vec3 origin;
    Vec3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;

    Camera();

    [[nodiscard]] Ray getRay(const float &u, const float &v) const;
};


#endif //RAY_TRACING_CAMERA_H
