### Top Level CMake Script for ND-Grad ###
cmake_minimum_required(VERSION 3.15.0)
project(NDGrad VERSION 1.0.0)


### Options ###
option(courses_build_all            "Builds nd-coursework applications, corresponding unit tests, and corresponding code samples." OFF)
option(courses_build_tests          "Builds nd-coursework applications and corresponding unit tests." OFF)
option(courses_build_samples        "Builds nd-coursework applications and corresponding code samples." OFF)
option(courses_exclude_scripts      "Builds nd-coursework applications while ignoring the scripts directory." OFF)

option(grad_build_all               "Builds all applications, unit tests, and code samples." OFF)
option(grad_build_tests             "Builds all applications and unit tests." OFF)
option(grad_build_samples           "Builds all applications and code samples." OFF)
option(grad_enable_coverage         "Builds all applications, unit tests, and enables coverage options." OFF)
option(grad_format_codebase         "Builds appropriate applications while also formatting the code." OFF)

option(research_build_all           "Builds nd-research applications, corresponding unit tests, and corresponding code samples." OFF)
option(research_build_tests         "Builds nd-research applications and corresponding unit tests." OFF)
option(research_build_samples       "Builds nd-research applications and corresponding code samples." OFF)
option(research_exclude_npgBuilder  "Builds nd-research applications without including NPG-Builder and its dependencies." OFF)
option(research_exclude_scripts     "Builds nd-research applications while ignoring the scripts directory." OFF)

## Set appropriate option flags and continue ##
if (grad_format_codebase)
    find_program(formatter clang-format HINTS /opt/local/libexec/llvm-16/bin/)

    if (NOT formatter_NOTFOUND)
        message(STATUS "Formatting ND-Grad")

        ## Run clang-format on all code except the files passed as arguments with the '-i' flag ##
        execute_process(COMMAND bash cmake/scripts/format-codebase.sh 
                                        -f ${formatter}
                                        -i nd-research/src/applications/misc/squareMatrix.cpp
                                        -i nd-research/src/applications/misc/utils.cpp
                        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                        OUTPUT_QUIET)
    endif()
endif()

if (grad_enable_coverage)
    set(grad_build_tests ON)
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} --coverage)
endif()

if (grad_build_all)
    set(courses_build_all ON)
    set(grad_build_tests ON)
    set(grad_build_samples ON)
    set(research_build_all ON)
endif()

if (grad_build_tests)
    set(courses_build_tests ON)
    set(research_build_tests ON)
endif()

if (grad_build_samples)
    set(courses_build_samples ON)
    set(research_build_samples ON)
endif()

if (courses_build_all)
    set(courses_build_tests ON)
    set(courses_build_samples ON)

    if (NOT grad_build_all AND NOT grad_build_tests AND NOT grad_build_samples
        AND NOT research_build_all AND NOT research_build_tests AND NOT research_build_samples)
        set(grad_exclude_research ON)
    endif()
endif()

if (research_build_all)
    set(research_build_tests ON)
    set(research_build_samples ON)

    if (NOT grad_build_all AND NOT grad_build_tests AND NOT grad_build_samples
        AND NOT courses_build_all AND NOT courses_build_tests AND NOT courses_build_samples)
        set(grad_exclude_courses ON)
    endif()
endif()


### Compilation Options ###
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (NOT WIN32)
    add_compile_options(-Wall -Wextra -pedantic -Werror)

    if (CMAKE_COMPILER_IS_GNUCXX)
        add_definitions(-Wno-psabi)
    endif()
endif()


### Functions ###
include(cmake/grad-utility-functions.cmake)


### External Modules ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(DryChem REQUIRED)

if (NOT ${DryChem_FOUND})
    ## If DryChem isn't installed or can't be found, download it from github ##
    NDGradExternalDownload(PROJECT DryChem
                           REPOSITORY "https://github.com/crdrisko/drychem.git"
                           TAG main)

    set(COMMON_UTILS_INCLUDE_DIR "${DryChem_SOURCE_DIR}/common-utilities/include")
    set(CPP_UNITS_INCLUDE_DIR "${DryChem_SOURCE_DIR}/cpp-units/include")
    set(DryChem_FOUND TRUE)
endif()

include_directories(${COMMON_UTILS_INCLUDE_DIR})
include_directories(${CPP_UNITS_INCLUDE_DIR})

find_package(DryPhys REQUIRED)

# if (NOT ${DryPhys_FOUND})
    ## If DryPhys isn't installed or can't be found, download it from github ##
    include(FetchContent)

    ## DryPhys
    message(STATUS "Fetching DryPhys...")
    FetchContent_Declare(dryphys        # v1.90.5
                         GIT_REPOSITORY "https://github.com/crdrisko/dryphys.git"
                         GIT_TAG dev)

    set(phys_exclude_engine OFF)

    FetchContent_MakeAvailable(dryphys)
    set(DryPhys_FOUND TRUE)

    include_directories(${dryphys_SOURCE_DIR}/include)
    include_directories("${dryphys_BINARY_DIR}") # for <config.h> -> need to fix in DryPhys...
# else()
#     include_directories(${DryPhys_LIBRARIES})
# endif()


### ND-Grad Subprojects ###
if (NOT grad_exclude_courses)
    # add_subdirectory(nd-coursework)
endif()

if (NOT grad_exclude_research)
    include_directories(nd-research/include)
    add_subdirectory(nd-research)
endif()
