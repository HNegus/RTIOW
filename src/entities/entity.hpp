#pragma once

#include <memory>

#include "utils/ray.hpp"
#include "utils/interval.hpp"

struct Material;

struct HitRecord {
    Point3 position{};
    Vec3 normal{};
    real_type t = 0;

    bool front_facing = false;

    std::shared_ptr<Material> material;

    inline void SetFaceNormal(const Ray& ray, const Vec3& outward_normal)
    {
        front_facing = ray.direction.Dot(outward_normal);
        normal = front_facing ? outward_normal : -outward_normal;
    }
};


class Entity {
public:

    virtual ~Entity() = default;

    virtual bool Hit(const Ray& ray, Interval interval,
                     HitRecord& record) const = 0;

public:
};