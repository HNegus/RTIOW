#pragma once

#include "common.hpp"

class Interval {
public:
    real_type min, max;

    // Default interval is empty/invalid.
    Interval() : min{+infinity}, max{-infinity} {};
    Interval(real_type _min, real_type _max) : min{_min}, max{_max} {};

    inline bool Contains(real_type x) const
    {
        return min <= x && x <= max;
    }

    inline bool Surrounds(real_type x) const
    {
        return min < x && x < max;
    }

    inline real_type Clamp(real_type x) const
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    inline Vec3 Clamp(Vec3 v) const
    {
        return Vec3(Clamp(v.x), Clamp(v.y), Clamp(v.z));
    }

    static const Interval empty;
    static const Interval universe;

};
inline const Interval Interval::empty;
inline const Interval Interval::universe(-infinity, infinity);