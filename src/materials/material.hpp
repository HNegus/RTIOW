#pragma once

#include "utils/ray.hpp"
#include "utils/color.hpp"

struct HitRecord;

struct Material {

    virtual ~Material() = default;

    virtual bool Scatter(const Ray& in, const HitRecord& record,
                        Color& attenuation, Ray& out) const = 0;
};