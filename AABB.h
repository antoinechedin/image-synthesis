//
// Created by antoine on 27/10/2019.
//

#ifndef RAY_TRACING_AABB_H
#define RAY_TRACING_AABB_H


#include "Vec3.h"
#include "Ray.h"

class AABB {
private:
    static float ffmin(const float &a, const float &b);

    static float ffmax(const float &a, const float &b);

public:
    Vec3 min;
    Vec3 max;

    AABB();

    AABB(const Vec3 &min, const Vec3 &max);

    [[nodiscard]] bool hit(const Ray &ray, float tmin, float tmax) const;

    static AABB surroundingBox(const AABB &box1, const AABB &box2);
};


#endif //RAY_TRACING_AABB_H
