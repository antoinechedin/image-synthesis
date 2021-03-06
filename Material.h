#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H


#include <random>
#include "Ray.h"
#include "RaycastHit.h"

class RaycastHit;

class Material {
public:
    virtual bool scatter(
            const Ray &rayIn,
            const RaycastHit &hit,
            Vec3 &attenuation,
            Ray &rayOut,
            std::default_random_engine &generator
    ) const = 0;

    static Vec3 randomDirInHemisphereCosWeight(const Vec3 &normal, std::default_random_engine &generator);

    static Vec3 randomDirInHemisphereCosWeight(
            const Vec3 &normal,
            const float &thetaMax,
            std::default_random_engine &generator
    );

    static Vec3 changeBase(const Vec3 &vec, const Vec3 &normal);

    static Vec3 reflectVec(const Vec3 &vec, const Vec3 &normal);

    static bool refract(const Vec3 &dirIn, const Vec3 &normal, const float &niOverNt, Vec3 &refracted);

    static float schlick(const float &cosine, const float &refractiveIndex);
};

class Lambertian : public Material {
public:
    Vec3 albedo;

    Lambertian(const Vec3 &albedo);

    bool scatter(
            const Ray &rayIn,
            const RaycastHit &hit,
            Vec3 &attenuation,
            Ray &rayOut,
            std::default_random_engine &generator
    ) const override;
};

class Metal : public Material {
public:
    Vec3 albedo;
    float fuzziness;

    Metal(const Vec3 &albedo, const float &fuzziness);

    bool scatter(
            const Ray &rayIn,
            const RaycastHit &hit,
            Vec3 &attenuation,
            Ray &rayOut,
            std::default_random_engine &generator
    ) const override;
};

class Dielectric : public Material {
public:
    Vec3 albedo;
    float refractiveIndex;

    Dielectric(const Vec3 &albedo, const float &refractiveIndex);

    bool scatter(
            const Ray &rayIn,
            const RaycastHit &hit,
            Vec3 &attenuation,
            Ray &rayOut,
            std::default_random_engine &generator
    ) const override;
};

#endif //RAY_TRACING_MATERIAL_H
