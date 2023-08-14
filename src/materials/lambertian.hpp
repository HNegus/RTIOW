#pragma once

#include "material.hpp"
#include "utils/color.hpp"

struct Diffuse : public Material {
    Color albedo{};

    Diffuse(const Color& c) : albedo {c} {};


    bool Scatter(const Ray& in, const HitRecord& record,
        Color& attenuation, Ray& out) const override;
};

struct Lambertian : public Material {
    Color albedo{};

    Lambertian(const Color& c) : albedo{c} {};

    bool Scatter(const Ray& in, const HitRecord& record,
        Color& attenuation, Ray& out) const override;
};