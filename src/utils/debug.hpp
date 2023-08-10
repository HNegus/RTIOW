#include <cassert>

#if defined(__GNUC__)
    #define RTA_COMPILER_GCC
    #include <signal.h>
    #define RTA_DEBUGBREAK raise(SIGTRAP)
#elif defined(__clang__)
    #define RTA_COMPILER_CLANG
    #if __has_builtin(__builtin_debugtrap)
        #define RTA_DEBUGBREAK __builtin_debugtrap
    #else
        #include <signal.h>
    #define RTA_DEBUGBREAK raise(SIGTRAP)
#endif
#elif defined(_MSC_VER)
    #define RTA_COMPILER_MSVC
    #define RTA_DEBUGBREAK __debugbreak
#endif

