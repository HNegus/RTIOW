#pragma once

#include "vec3.hpp"
#include "common.hpp"

class Ray {

public:

    Ray() {}
    Ray(const Point3& orig, const Vec3 dir) : origin{orig}, direction{dir} {}
    Point3 At(real_type t) const
    {
        return origin + t*direction;
    }

    Point3 origin{};
    Vec3 direction{};

};