#include "Material.h"

Vec3 Material::randomDirInHemisphereCosWeight(const Vec3 &normal, std::default_random_engine &generator) {
    std::uniform_real_distribution dist(0.0f, 1.0f);
    float r1 = dist(generator);
    float r2 = dist(generator);
    float x = cosf(2.0f * float(M_PI) * r1) * sqrtf(1 - r2);
    float y = sinf(2.0f * float(M_PI) * r1) * sqrtf(1 - r2);
    float z = sqrtf(r2);

    return Material::changeBase(Vec3(x, y, z), normal);
}

Vec3 Material::randomDirInHemisphereCosWeight(const Vec3 &normal, const float &thetaMax,
                                              std::default_random_engine &generator) {
    std::uniform_real_distribution dist(0.0f, 1.0f);
    float r1 = dist(generator);
    float r2 = dist(generator);
    float x = cosf(2.0f * float(M_PI) * r1) * sinf(thetaMax) * sqrtf(r2);
    float y = sinf(2.0f * float(M_PI) * r1) * sinf(thetaMax) * sqrtf(r2);
    float z = sqrtf(1 - r2 * sinf(thetaMax) * sinf(thetaMax));

    return Material::changeBase(Vec3(x, y, z), normal);
}

Vec3 Material::changeBase(const Vec3 &vec, const Vec3 &normal) {
    Vec3 bx(1, 2, 3);
    Vec3 by = Vec3::cross(normal, bx.unit()).unit();
    bx = Vec3::cross(by, normal).unit();
    return Vec3(vec.x * bx + vec.y * by + vec.z * normal);
}

Vec3 Material::reflectVec(const Vec3 &vec, const Vec3 &normal) {
    return vec - 2.0f * Vec3::dot(vec, normal) * normal;
}

bool Material::refract(const Vec3 &dirIn, const Vec3 &normal, const float &niOverNt, Vec3 &refracted) {
    float dt = Vec3::dot(dirIn, normal);
    float discriminant = 1.0f - niOverNt * niOverNt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = niOverNt * (dirIn - normal * dt) - normal * sqrtf(discriminant);
        return true;
    } else
        return false;
}

float Material::schlick(const float &cosine, const float &refractiveIndex) {
    float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * powf((1 - cosine), 5);
}

Lambertian::Lambertian(const Vec3 &albedo) : albedo(albedo) {}

bool Lambertian::scatter(
        const Ray &rayIn,
        const RaycastHit &hit,
        Vec3 &attenuation,
        Ray &rayOut,
        std::default_random_engine &generator
) const {
    attenuation = albedo;
    Vec3 newDir = randomDirInHemisphereCosWeight(hit.normal, generator);
    rayOut = Ray(hit.point, newDir);
    return true;
}

Metal::Metal(const Vec3 &albedo, const float &fuzziness) : albedo(albedo), fuzziness(fuzziness) {}

bool Metal::scatter(
        const Ray &rayIn,
        const RaycastHit &hit,
        Vec3 &attenuation,
        Ray &rayOut,
        std::default_random_engine &generator
) const {
    attenuation = albedo;
    Vec3 newDir = reflectVec(rayIn.direction, hit.normal);
    if (fuzziness > 0) {
        newDir = Material::randomDirInHemisphereCosWeight(newDir, fuzziness, generator);
    }
    rayOut = Ray(hit.point, newDir);
    return (Vec3::dot(rayOut.direction, hit.normal) > 0);
}

Dielectric::Dielectric(const Vec3 &albedo, const float &refractiveIndex) :
        refractiveIndex(refractiveIndex), albedo(albedo) {}

bool Dielectric::scatter(
        const Ray &rayIn,
        const RaycastHit &hit,
        Vec3 &attenuation,
        Ray &rayOut,
        std::default_random_engine &generator
) const {
    attenuation = albedo;
    Vec3 outwardNormal;
    Vec3 reflected = Material::reflectVec(rayIn.direction, hit.normal);
    float niOverNt;
    Vec3 refracted;

    float reflectProba;
    float cosine;

    if (Vec3::dot(rayIn.direction, hit.normal) > 0) {
        outwardNormal = -1.0f * hit.normal;
        niOverNt = refractiveIndex;
        cosine = refractiveIndex * Vec3::dot(rayIn.direction, hit.normal);
    } else {
        outwardNormal = hit.normal;
        niOverNt = 1.0f / refractiveIndex;
        cosine = -Vec3::dot(rayIn.direction, hit.normal);
    }

    if (refract(rayIn.direction, outwardNormal, niOverNt, refracted)) {
        reflectProba = Material::schlick(cosine, refractiveIndex);
    } else {
        reflectProba = 1.0;
    }
    std::uniform_real_distribution dist(0.0, 1.0);
    if (dist(generator) < reflectProba) {
        rayOut = Ray(hit.point, reflected);
    } else {
        rayOut = Ray(hit.point, refracted);
    }
    return true;
}
