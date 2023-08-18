#include "common.hpp"

#include <cstdlib>

real_type RandomReal()
{
    return rand() / ((real_type)RAND_MAX+1);
}

real_type RandomNumber(real_type min, real_type max)
{
    return min + (max - min) * RandomReal();
}
