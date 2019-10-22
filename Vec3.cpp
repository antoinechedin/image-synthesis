#include <cmath>
#include "Vec3.h"

Vec3::Vec3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vec3::Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vec3::squaredNorm() const {
    return x * x + y * y + z * z;
}

float Vec3::norm() const {
    return std::sqrt(this->squaredNorm());
}

Vec3 Vec3::unit() const {
    return *this / norm();
}

float Vec3::dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 Vec3::cross(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
    );
}

bool Vec3::operator==(const Vec3 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z;
}

bool Vec3::operator!=(const Vec3 &rhs) const {
    return !(rhs == *this);
}

Vec3 Vec3::operator+(const Vec3 &rhs) const {
    return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vec3 Vec3::operator-(const Vec3 &rhs) const {
    return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3 Vec3::operator/(const float &t) const {
    return Vec3(x / t, y / t, z / t);
}

Vec3 Vec3::operator*(const Vec3 &lhs) const {
    return Vec3(x * lhs.x, y * lhs.y, z * lhs.z);
}

Vec3 Vec3::operator*(const float &t) const {
    return Vec3(x * t, y * t, z * t);
}

Vec3 operator*(const float &t, const Vec3 &vec3) {
    return vec3 * t;
}

Vec3 &Vec3::operator+=(const Vec3 &rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}

Vec3 &Vec3::operator/=(const float &t) {
    this->x /= t;
    this->y /= t;
    this->z /= t;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vec3 &vec3) {
    os << "[" << vec3.x << ", " << vec3.y << "," << vec3.z << "]";
    return os;
}


