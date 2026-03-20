cmake_minimum_required(VERSION 4.2.3)
project(arenastl)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE sources
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

add_definitions(-DSOME_DEFINITION)

add_executable(app ${sources})

target_compile_options(app PRIVATE
    -g
    -O0
    -fsanitize=address,undefined
    -fno-omit-frame-pointer
)

target_link_options(app PRIVATE
    -fsanitize=address,undefined
)
