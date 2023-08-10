#pragma once

#include "vec3.hpp"


class Color : public Vec3 {
public:
    using Vec3::Vec3;
    using Vec3::operator=;
    Color(Vec3&& v) : Vec3(v) {}
};

inline std::ostream& operator<<(std::ostream &out, Color color)
{
    out << static_cast<int>(255.9999 * color.r) << " "
        << static_cast<int>(255.9999 * color.g) << " "
        << static_cast<int>(255.9999 * color.b);
    return out;
}