#pragma once

#include "material.hpp"

struct Dielectric : public Material {

    Color albedo{};
    real_type ior;

    Dielectric(real_type index_of_refraction, const Color& c)
        : albedo{c}
        , ior{index_of_refraction}
    {}
    Dielectric(real_type index_of_refraction) : Dielectric(index_of_refraction, Color(1)) {}

    virtual bool Scatter(const Ray& in, const HitRecord& record,
        Color& attenuation, Ray& out) const override;

private:
    static real_type Reflectance(real_type cosine, real_type ref_idx);
};