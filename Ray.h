#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H


#include "Vec3.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray();

    Ray(const Vec3 &origin, const Vec3 &direction);

    [[nodiscard]] Vec3 pointAt(float t) const;
};


#endif //RAY_TRACING_RAY_H
