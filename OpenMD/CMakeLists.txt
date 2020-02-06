### Files / Directories ###
set(SOURCES
    rnemd/src/rnemdFile.cpp
    rnemd/src/rnemdRegion.cpp)

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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/lib
    CACHE PATH
    "Single directory for all static libraries.")


### Libraries / Executables ###
include_directories(${CMAKE_INSTALL_PREFIX}/include)

add_library(openmd-plugin SHARED ${SOURCES})
find_library(Utilities_API utilities-api HINTS ${CMAKE_INSTALL_PREFIX}/lib)
target_link_libraries(openmd-plugin PUBLIC ${Utilities_API})

add_library(openmd-plugin-static STATIC ${SOURCES})
find_library(Utilities_API_static utilities-api-static HINTS ${CMAKE_INSTALL_PREFIX}/lib)
target_link_libraries(openmd-plugin-static PUBLIC ${Utilities_API_static})


### Installation ###
install(TARGETS openmd-plugin openmd-plugin-static
        DESTINATION lib)

install(DIRECTORY rnemd/include/
        DESTINATION include/nd-research/openmd)

foreach (BASH_FILE ${BASH_FILES})
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
    function (new_test testname interiorDirectory)
        add_executable(test${testname} test/${interiorDirectory}/test${testname}.cpp)

        target_link_libraries(test${testname} ${GTEST_LIBRARIES} openmd-plugin)

        gtest_discover_tests(test${testname}
                             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/${interiorDirectory})
    endfunction()

    ## Locate GTest ##
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    ## Create all tests ##
    new_test(ChargedRNEMDParameters TestChargedRNEMD)
    new_test(CurrentRNEMD TestFluxTypes/FluxType_Current)
    new_test(KE_RNEMD TestFluxTypes/FluxType_KE)
    new_test(Px_RNEMD TestFluxTypes/FluxType_Px)
    new_test(SingleRNEMD TestFluxTypes/FluxType_Single)
endif()
