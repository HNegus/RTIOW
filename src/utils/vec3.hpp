#pragma once

#include <cmath>
#include <iostream>

#include "debug.hpp"
#include "common.hpp"

struct Vec3;
using Point3 = Vec3;

// disable anonymous struct warning
#ifdef RTA_COMPILER_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#elif defined(RTA_COMPILER_CLANG)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
    #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined(RTA_COMPILER_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4201)  // nonstandard extension used : nameless struct/union
#endif

#ifdef RTA_USE_SIMD
struct alignas(16) Vec3 {
#else
struct Vec3 {
#endif
    using value_type = real_type;
    union
    {
        struct { value_type x, y, z; };
        struct { value_type r, g, b; };
        value_type v[3];
    };

    Vec3(value_type all) : x{all}, y{all}, z{all} {}
    Vec3(value_type a, value_type b, value_type c) : x{a}, y{b}, z{c} {}
    Vec3() : Vec3(0, 0, 0) {}

    Vec3 operator-() const { return Vec3(-x, -y, -z); }
    value_type operator[](int i) const {
        switch (i) {
            case 0:
            case 1:
            case 2:
                return v[i];
        }

        assert(false && "Vec3 index out of bounds");
    }
    value_type& operator[](int i) {
        switch (i)  {
            case 0:
            case 1:
            case 2:
                return v[i];
        }

        assert(false && "Vec3 index out of bounds");
     }

    Vec3& operator+=(const Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3& operator-=(const Vec3 &v)
    {
        *this += -v;
        return *this;
    }

    Vec3& operator*=(value_type r)
    {
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }

    Vec3& operator/=(value_type r)
    {
        *this *= 1/r;
        return *this;
    }

    value_type Length() const
    {
        return std::sqrt(this->Dot(*this));
    }

    value_type Dot(const Vec3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3 Cross(const Vec3& v) const
    {
        return Vec3(y * v.z - z * v.y,
                    z * v.x - x * v.z,
                    x * v.y - y * v.x);
    }

    Vec3 Unit() const
    {
        Vec3 v(*this);
        v /= Length();
        return v;
    }

    static Vec3 Random()
    {
        return Vec3(RandomReal(), RandomReal(), RandomReal());
    }

    static Vec3 Random(real_type min, real_type max)
    {
        return Vec3(RandomNumber(min, max),
                    RandomNumber(min, max),
                    RandomNumber(min, max));
    }

    static Vec3 RandomUnit()
    {
        while (true) {
            Vec3 v = Random();
            if (v.Dot(v) < 1) {
                return v.Unit();
            }
        }
    }

    static Vec3 RandomOnHemisphere(const Vec3& normal)
    {
        Vec3 unit = RandomUnit();
        if (unit.Dot(normal) > 0) {
            return unit;
        }
        return -unit;
    }
};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.x << " " << v.y << " " << v.z;
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return u + -v;
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator/(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.x / v.x, u.y / v.y, u.z / v.z);
}

inline Vec3 operator+(const Vec3 &v, Vec3::value_type r)
{
    return Vec3(v.x + r, v.y + r, v.z + r);
}

inline Vec3 operator+(Vec3::value_type r, const Vec3 &v)
{
    return v + r;
}

inline Vec3 operator-(const Vec3 &v, Vec3::value_type r)
{
    return v + -r;
}

inline Vec3 operator-(Vec3::value_type r, const Vec3 &v)
{
    return v - r;
}

inline Vec3 operator*(const Vec3& v, Vec3::value_type r)
{
    return Vec3(v.x * r, v.y * r, v.z * r);
}

inline Vec3 operator*(Vec3::value_type r, const Vec3 &v)
{
    return v * r;
}

inline Vec3 operator/(const Vec3 &v, Vec3::value_type r)
{
    return v * (1/r);
}

inline Vec3 operator/(Vec3::value_type r, const Vec3 &v)
{
    return v / r;
}

// enable anonymous struct warning
#ifdef RTA_COMPILER_CLANG
    #pragma clang diagnostic pop
#elif defined(RTA_COMPILER_GCC)
    #pragma GCC diagnostic pop
#elif defined(RTA_COMPILER_CLANG)
    #pragma warning(pop)
#endif