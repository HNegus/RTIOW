#include "rng.hpp"

#include <random>

static thread_local std::mt19937 generator(0);

real_type RandomNumber(real_type min, real_type max)
{
    thread_local std::uniform_real_distribution<> dis(min, max);
    return dis(generator);
}

real_type RandomReal()
{
    return RandomNumber(0, 1);
}


