#include "rng.hpp"

#include <random>

static thread_local std::mt19937 generator(0);

real_type RandomReal(real_type min, real_type max)
{
    thread_local std::uniform_real_distribution<> dis(min, max);
    return dis(generator);
}

int RandomInt(int32_t min, int32_t max)
{
    thread_local std::uniform_int_distribution<> dis(min, max);
    return dis(generator);
}

int RandomInt()
{
    return RandomInt(INT32_MIN, INT32_MAX);
}

real_type RandomReal()
{
    return RandomReal(0, 1);
}


