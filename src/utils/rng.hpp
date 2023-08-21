#pragma once

#include "common.hpp"
#include <cstdint>

/* TODO
 * - put functions in in namespace
 * - specify distribution type (uniform, normal, etc.)
 */

// namespace Random {
    int RandomInt();
    int RandomInt(int32_t min, int32_t max);
    real_type RandomReal();
    real_type RandomReal(real_type min, real_type max);
// }




