cmake_minimum_required(VERSION 3.12.0)
project(raytrace VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

set(CMAKE_CXX_STANDARD 20)

add_executable(raytrace ${SOURCES})

target_include_directories(raytrace PRIVATE src)

target_compile_options(raytrace PRIVATE
    -Wall -Wextra -Wpedantic
    # -fsanitize=address
    -Wfloat-conversion
    )

target_link_libraries(raytrace PUBLIC
    tbb
    )

# if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_compile_options(raytrace PRIVATE
#         -Wfloat-conversion
#     )
# elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#     target_compile_options(raytrace PRIVATE
#         -Wint-in-bool-context
#     )
# endif()

target_link_options(raytrace PRIVATE
    # -fsanitize=address
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
