#include "metal.hpp"

#include "entities/entity.hpp"

bool Metal::Scatter(const Ray& in, const HitRecord& record,
            Color& attenuation, Ray& out) const
{
    Vec3 reflected = in.direction.Unit().Reflect(record.normal);
    out = Ray(record.position, reflected);
    attenuation = albedo;
    return true;
}