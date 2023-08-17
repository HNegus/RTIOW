#include "dielectric.hpp"

#include "entities/entity.hpp"

bool Dielectric::Scatter(const Ray& in, const HitRecord& record,
    Color& attenuation, Ray& out) const
{
    attenuation = albedo;
#ifdef REFRACT
    bool reflect = RandomReal() < 0.5;
    if (reflect) {
        Vec3 reflected = in.direction.Unit().Reflect(record.normal);
        out = Ray(record.position, reflected);
        return true;
    }
#endif

    real_type refraction_ratio = record.front_facing ? (1.0/ior) : ior;
    Vec3 unit_direction = in.direction.Unit();
    Vec3 refracted = unit_direction.Refract(record.normal, refraction_ratio);

    out = Ray(record.position, refracted);


    return true;
}