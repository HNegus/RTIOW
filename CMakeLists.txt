cmake_minimum_required(VERSION 3.12.0)
project(raytrace VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Variables
set(CMAKE_CXX_STANDARD 20)

set(RTA_ENABLE_THREADS ON CACHE BOOL "Enable multi-threading")
set(RTA_FAST_MATH ON CACHE BOOL "Enable -ffast-math optimisations")
set(RTA_USE_SANITIZER "" CACHE STRING "Use sanitizer (ASAN/TSAN)")

# Source files are all in src
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(raytrace ${SOURCES})
target_include_directories(raytrace PRIVATE src)

target_compile_options(raytrace PRIVATE
    -Wall -Wextra -Wpedantic
    -Wfloat-conversion
    )

if (RTA_FAST_MATH)
    target_compile_options(raytrace PRIVATE
        -ffast-math
    )
endif()

# Enable sanitizers
if (RTA_USE_SANITIZER EQUAL ASAN)
    target_compile_options(raytrace PRIVATE -fsanitize=address)
    target_link_options(raytrace PRIVATE -fsanitize=address)
elseif (RTA_USE_SANITIZER EQUAL TSAN)
    target_compile_options(raytrace PRIVATE -fsanitize=thread)
    target_link_options(raytrace PRIVATE -fsanitize=thread)
endif ()

if (RTA_ENABLE_THREADS)
    target_link_libraries(raytrace PRIVATE tbb)
    target_compile_definitions(raytrace PRIVATE RTA_ENABLE_THREADS)
endif()


# Build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "-ffast-math enabled: ${RTA_FAST_MATH}")
message(STATUS "Threading = ${RTA_ENABLE_THREADS}")
if (RTA_USE_SANITIZER)
    message(STATUS "Sanitizer = ${RTA_USE_SANITIZER}")
endif()
get_property(COMPILE_DEFINITIONS TARGET raytrace PROPERTY COMPILE_DEFINITIONS)
message(STATUS "Preprocessor definitions: ${COMPILE_DEFINITIONS}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
