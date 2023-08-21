#include "aabb.hpp"

#include <cmath>


bool AABB::Hit(const Ray& ray, Interval ray_t) const
{
#define RTA_OPTIMIZED
#ifndef RTA_OPTIMIZED
    for (int i = 0; i < 3; i++) {
        const Interval& axis = (*this)[i];
        const real_type factor = ray.origin[i] / ray.direction[i];

        auto t0 = fmin(axis.min - factor, axis.max - factor);
        auto t1 = fmax(axis.min - factor, axis.max - factor);
        ray_t.min = fmax(t0, ray_t.min);
        ray_t.max = fmin(t1, ray_t.max);
        if (ray_t.max <= ray_t.min) {
            return false;
        }
    }
    return true;
#else
    for (int i = 0; i < 3; i++) {
        auto invD = 1 / ray.direction[i];
        auto orig = ray.origin[i];

        auto t0 = ((*this)[i].min - orig) * invD;
        auto t1 = ((*this)[i].max - orig) * invD;

        if (invD < 0)
            std::swap(t0, t1);

        if (t0 > ray_t.min)
            ray_t.min = t0;
        if (t1 < ray_t.max)
            ray_t.max = t1;

        if (ray_t.max <= ray_t.min)
            return false;
    }
    return true;

#endif

}