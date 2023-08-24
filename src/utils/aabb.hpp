#pragma once

#include "interval.hpp"
#include "ray.hpp"

class AABB {
public:

    static const AABB empty, universe;

    Interval x, y, z;

    AABB() = default;
    AABB(const Interval& ix, const Interval& iy, const Interval& iz)
        : x{ix}, y{iy}, z{iz}
    {}
    AABB(const Point3& a, const Point3 b)
        : x{Interval(fmin(a.x, b.x), fmax(a.x, b.x))}
        , y{Interval(fmin(a.y, b.y), fmax(a.y, b.y))}
        , z{Interval(fmin(a.z, b.z), fmax(a.z, b.z))}
    {}
    AABB(const AABB& first, const AABB& second)
        : x{Interval(first.x, second.x)}
        , y{Interval(first.y, second.y)}
        , z{Interval(first.z, second.z)}
    {}
    AABB(const Interval& interval)
        : AABB(interval, interval, interval)
    {}

    bool Hit(const Ray& ray, Interval ray_t) const;

    uint32_t LongestAxis() const
    {
        if (x.Size() > y.Size()) {
            return x.Size() > z.Size() ? 0 : 2;
        }
        return y.Size() > z.Size() ? 1 : 2;
    }

    const Interval& operator[](size_t i) const
    {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
        }

        throw std::out_of_range("Vec3 index out of bounds");
    }

};

inline const AABB AABB::empty(Interval::empty), AABB::universe(Interval::universe);