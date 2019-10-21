#include "Ray.h"

Ray::Ray() {
    this->origin = Vec3();
    this->direction = Vec3();
}

Ray::Ray(const Vec3 &origin, const Vec3 &direction) {
    this->origin = origin;
    this->direction = direction;
}

Vec3 Ray::pointAt(float t) const {
    return Vec3(origin + t * direction);
}
