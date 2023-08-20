#pragma once

#include "vec3.hpp"
#include "common.hpp"

class Ray {

public:
    Ray() {}
    Ray(const Point3& orig, const Vec3& dir, real_type t)
        : origin{orig}, direction{dir}, time{t}
    {}
    Ray(const Point3& orig, const Vec3& dir) : Ray(orig, dir, 0) {}

    Point3 At(real_type t) const
    {
        return origin + t*direction;
    }
    Vec3 AsUnit() const
    {
        return (direction - origin).Unit();
    }

    Point3 origin{};
    Vec3 direction{};
    real_type time = 0;

};