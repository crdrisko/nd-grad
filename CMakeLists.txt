### Top Level CMake Script for ND-Research ###
cmake_minimum_required(VERSION 3.10.0)
project(ND-Research VERSION 1.0.0)


### Compilation Options ###
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_compile_options(-Wall -Wextra -pedantic -Werror)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wno-psabi)
endif()


### The ND-Research Projects to Include ###
add_subdirectory(OpenMD)
