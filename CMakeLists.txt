### Top level cmake script for ND-Research ###
cmake_minimum_required(VERSION 3.10.0)
project(ND-Research VERSION 1.0.0)


### Compilation Options ###
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions("-Wno-psabi")
endif()


### Files / Directories ###
set(SOURCES 
    src/OpenMD/src/rnemdFile.cpp
    src/OpenMD/src/rnemdRegion.cpp)

set(BASH_FILES
    scripts/groupSubmit.sh)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 
    ${PROJECT_BINARY_DIR}/lib
    CACHE PATH 
    "Single directory for all shared libraries.")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH 
    "Single directory for all executables.")

find_library(Utilities_API utilities-api REQUIRED)
include_directories(/usr/local/include/)


### Libraries / Executables ###
add_library(openmd-plugin SHARED ${SOURCES})
target_link_libraries(openmd-plugin ${Utilities_API})


### Installation ###
install(TARGETS openmd-plugin
        DESTINATION lib)
        
install(DIRECTORY src/OpenMD/include/
        DESTINATION include/nd-research/openmd)

foreach(BASH_FILE ${BASH_FILES})
    ## Remove bash extensions and make scripts executable ##
    get_filename_component(filename "${BASH_FILE}" NAME_WE)

    configure_file(${BASH_FILE} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${filename}" @ONLY)

    install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${filename}"
            DESTINATION bin
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE 
                        GROUP_READ             GROUP_EXECUTE 
                        WORLD_READ             WORLD_EXECUTE)
endforeach()


### Unit Testing ###
option(build_all_tests "Build all unit tests in the test directory." OFF)

if (build_all_tests)
    include(CTest)
    include(GoogleTest)

    enable_testing()

    ## Function to create a new test based off the pre-defined naming template ##
    function(new_test testname interiorDirectory)
        add_executable(test${testname}Functions test/${interiorDirectory}/test${testname}.cpp)

        target_link_libraries(test${testname}Functions ${GTEST_LIBRARIES} openmd-plugin ${Utilities_API})
        
        gtest_discover_tests(test${testname}Functions 
                             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/${interiorDirectory})
    endfunction(new_test)

    ## Locate GTest ##
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    ## Create all tests ##
    new_test(CurrentRNEMD TestFluxTypes/FluxType_Current)
    new_test(KE_RNEMD TestFluxTypes/FluxType_KE)
    new_test(Px_RNEMD TestFluxTypes/FluxType_Px)
    new_test(SingleRNEMD TestFluxTypes/FluxType_Single)
endif()
