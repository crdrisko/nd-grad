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


### Functions ###
function(externalDownload)
    set(options)
    set(one_value_keywords PROJECT
                           REPOSITORY)
    set(multi_value_keywords)

    cmake_parse_arguments(EXTERN_ARGS "${options}" "${one_value_keywords}" "${multi_value_keywords}" ${ARGN})

    ## Download and unpack project at configure time ##
    configure_file(${ND-Research_SOURCE_DIR}/cmake/CMakeLists.txt.in ${EXTERN_ARGS_PROJECT}-download/CMakeLists.txt)

    ## Configuration step ##
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${EXTERN_ARGS_PROJECT}-download)
    if (result)
        message(FATAL_ERROR "CMake step for ${EXTERN_ARGS_PROJECT} failed: ${result}")
    endif()

    ## Build Step ##
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${EXTERN_ARGS_PROJECT}-download)
    if (result)
        message(FATAL_ERROR "Build step for ${EXTERN_ARGS_PROJECT} failed: ${result}")
    endif()

    ## Add project directly to our build ##
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/${EXTERN_ARGS_PROJECT}-download/${EXTERN_ARGS_PROJECT}-src
                     ${CMAKE_CURRENT_BINARY_DIR}/${EXTERN_ARGS_PROJECT}-download/${EXTERL_ARGS_PROJECT}-build
                     EXCLUDE_FROM_ALL)
endfunction()


### External Modules ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(Utilities_API REQUIRED)

if (NOT ${UTILITIES_API_FOUND})
    ## If utilities-api isn't installed or can't be found, download it from github ##
    externalDownload(PROJECT utilities-api
                     REPOSITORY "https://github.com/crdrisko/utilities-api.git")

    set(UTILITIES_API_INCLUDE_DIR "${Utilities-API_SOURCE_DIR}/include")
    set(UTILITIES_API_FOUND TRUE)
endif()

include_directories(${UTILITIES_API_INCLUDE_DIR})

find_package(CPP_Units REQUIRED)

if (NOT ${CPP_UNITS_FOUND})
    ## If cpp-units isn't installed or can't be found, download it from github ##
    externalDownload(PROJECT cpp-units
                     REPOSITORY "https://github.com/crdrisko/cpp-units.git")

    set(CPP_UNITS_INCLUDE_DIR "${CPP-Units_SOURCE_DIR}/include")
    set(CPP_UNITS_FOUND TRUE)
endif()

include_directories(${CPP_UNITS_INCLUDE_DIR})


### ND-Research Subprojects ###
add_subdirectory(nd-research)
