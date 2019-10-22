#ifndef RAY_TRACING_VEC3_H
#define RAY_TRACING_VEC3_H


class Vec3 {
public:
    float x;
    float y;
    float z;

    Vec3();

    Vec3(float x, float y, float z);

    [[nodiscard]] float squaredNorm() const;

    [[nodiscard]] float norm() const;

    [[nodiscard]] Vec3 unit() const;

    static float dot(const Vec3 &v1, const Vec3 &v2);

    static Vec3 cross(const Vec3 &v1, const Vec3 &v2);

    bool operator==(const Vec3 &rhs) const;

    bool operator!=(const Vec3 &rhs) const;

    Vec3 operator+(const Vec3 &rhs) const;

    Vec3 operator-(const Vec3 &rhs) const;

    Vec3 operator/(const float &t) const;

    Vec3 operator*(const Vec3 &lhs) const;

    Vec3 operator*(const float &t) const;

    friend Vec3 operator*(const float &t, const Vec3 &vec3);

    Vec3& operator+=(const Vec3 &rhs);

    Vec3& operator/=(const float &t);

};


#endif //RAY_TRACING_VEC3_H
