#include <cassert>

#if defined(__GNUC__)
    #define RTA_COMPILER_GCC
#elif defined(__clang__)
    #define RTA_COMPILER_CLANG
#elif defined(_MSC_VER)
    #define RTA_COMPILER_MSVC
#endif