#pragma once

#include "material.hpp"

struct HitRecord;

struct Metal : public Material {

    Color albedo{};

    Metal(const Color& c) : albedo{c} {};

    virtual bool Scatter(const Ray& in, const HitRecord& record,
        Color& attenuation, Ray& out) const override;
};