#pragma once

#include "material.hpp"

struct Metal : public Material {

    Color albedo{};
    real_type fuzz;

    Metal(const Color& c, real_type f) : albedo{c}, fuzz{f < 1 ? f : 1 } {}
    Metal(const Color& c) : Metal(c, 0) {};

    virtual bool Scatter(const Ray& in, const HitRecord& record,
        Color& attenuation, Ray& out) const override;
};