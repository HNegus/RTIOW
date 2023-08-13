#include "common.hpp"

#include <cstdlib>

real_type RandomReal()
{
    return ((real_type)rand()) / RAND_MAX;
}

real_type RandomNumber(real_type min, real_type max)
{
    return min + (max - min) * RandomReal();
}
