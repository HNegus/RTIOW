#include "dielectric.hpp"

#include "entities/entity.hpp"

bool Dielectric::Scatter(const Ray& in, const HitRecord& record,
    Color& attenuation, Ray& out) const
{
    attenuation = albedo;
// TODO remove?
#ifdef REFRACT
    bool reflect = RandomReal() < 0.5;
    if (reflect) {
        Vec3 reflected = in.direction.Unit().Reflect(record.normal);
        out = Ray(record.position, reflected);
        return true;
    }
#endif

    real_type refraction_ratio = record.front_facing ? (1.0f/ior) : ior;
    Vec3 unit_direction = in.direction.Unit();

    real_type cos_theta = static_cast<real_type>(fmin(-unit_direction.Dot(record.normal), 1.0));
    real_type sin_theta = static_cast<real_type>(sqrt(1.0f - cos_theta*cos_theta));

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;
    if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > RandomReal()) {
        direction = unit_direction.Reflect(record.normal);
    } else {
        direction = unit_direction.Refract(record.normal, refraction_ratio);
    }

    out = Ray(record.position, direction, in.time);
    return true;
}

real_type Dielectric::Reflectance(real_type cosine, real_type ref_idx)
{
    real_type r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * static_cast<real_type>(pow((1 - cosine), 5));
}
