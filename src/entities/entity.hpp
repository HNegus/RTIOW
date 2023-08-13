#pragma once

#include "utils/ray.hpp"
#include "utils/interval.hpp"

class HitRecord {
public:
    Point3 position{};
    Vec3 normal{};
    real_type t = 0;

    bool front_facing = false;

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
};