#pragma once

#include <limits>

using real_type = float;

constexpr real_type infinity = std::numeric_limits<real_type>::infinity();
constexpr real_type pi = 3.1415926535897932385f;

inline real_type constexpr DegToRad(real_type deg)
{
    return deg * pi / 180.0f;
}

real_type RandomReal();

real_type RandomNumber(real_type min, real_type max);