### Top Level CMake Script for ND-Research ###
cmake_minimum_required(VERSION 3.10.0)
project(ND-Research VERSION 1.0.0)


### Options ###
option(nd-research_build_tests "Build all unit tests in the test directory." OFF)
option(nd-research_coverage "Turn on coverage options for use with lcov, gcov, and/or coveralls." OFF)

if (nd-research_coverage)
    set(nd-research_build_tests ON)
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --coverage)
endif()


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


### Functions ###
include(cmake/nd-research_utilities.cmake)


### External Modules ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(Utilities_API REQUIRED)

if (NOT ${UTILITIES_API_FOUND})
    ## If utilities-api isn't installed or can't be found, download it from github ##
    nd-research_ExternalDownload(PROJECT utilities-api
                                 REPOSITORY "https://github.com/crdrisko/utilities-api.git")

    set(UTILITIES_API_INCLUDE_DIR "${Utilities-API_SOURCE_DIR}/include")
    set(UTILITIES_API_FOUND TRUE)
endif()

include_directories(${UTILITIES_API_INCLUDE_DIR})

find_package(CPP_Units REQUIRED)

if (NOT ${CPP_UNITS_FOUND})
    ## If cpp-units isn't installed or can't be found, download it from github ##
    nd-research_ExternalDownload(PROJECT cpp-units
                                 REPOSITORY "https://github.com/crdrisko/cpp-units.git")

    set(CPP_UNITS_INCLUDE_DIR "${CPP-Units_SOURCE_DIR}/include")
    set(CPP_UNITS_FOUND TRUE)
endif()

include_directories(${CPP_UNITS_INCLUDE_DIR})


### ND-Research SubProjects ###
add_subdirectory(nd-research)
