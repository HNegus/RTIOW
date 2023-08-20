#include "lambertian.hpp"

#include "entities/entity.hpp"

bool Diffuse::Scatter([[maybe_unused]] const Ray& in, const HitRecord& record,
            Color& attenuation, Ray& out) const
{
    const Vec3 scatter_direction = Vec3::RandomOnHemisphere(record.normal);
    attenuation = albedo;
    out = Ray(record.position, scatter_direction, in.time);
    return true;
}

bool Lambertian::Scatter([[maybe_unused]] const Ray& in, const HitRecord& record,
            Color& attenuation, Ray& out) const
{
    Vec3 scatter_direction = record.normal + Vec3::RandomUnit();
    // Special case when RandomUnit() ~ -normal;
    if (scatter_direction.NearZero()) {
        scatter_direction = record.normal;
    }
    attenuation = albedo;
    out = Ray(record.position, scatter_direction, in.time);
    return true;
}
