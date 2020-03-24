### Files / Directories ###
set(RNEMD_FILE_PARSING_SOURCES
    RNEMDFileParsing/src/rnemdFile.cpp
    RNEMDFileParsing/src/rnemdRegion.cpp)

set(CHARGED_RNEMD_SOURCES
    ChargedRNEMD/src/chargedRNEMD.cpp
    ChargedRNEMD/src/chargedRNEMDAnalysisMethod.cpp
    ChargedRNEMD/src/regionFitting.cpp
    ChargedRNEMD/src/regionDifference.cpp)

set(SHIFTXYZ_SOURCES
    ShiftXYZ/src/shiftXYZ.cpp
    ShiftXYZ/src/xyzFile.cpp)

set(SCRIPTS
    scripts/groupSubmit.sh
    scripts/equilibrator.sh
    ChargedRNEMD/scripts/plotOptimizationAnalysis.py)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single directory for all executables.")


### Libraries / Executables ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

find_package(Utilities_API REQUIRED)
include_directories(${UTILITIES_API_INCLUDE_DIR})

find_package(CPP_Units REQUIRED)
include_directories(${CPP_UNITS_INCLUDE_DIR})

add_executable(chargedRNEMD ${CHARGED_RNEMD_SOURCES} ${RNEMD_FILE_PARSING_SOURCES})
target_link_libraries(chargedRNEMD ${UTILITIES_API_LIBRARIES})

add_executable(shiftXYZ ${SHIFTXYZ_SOURCES})
target_link_libraries(shiftXYZ ${UTILITIES_API_LIBRARIES})


### Installation ###
install(TARGETS chargedRNEMD shiftXYZ
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ             GROUP_EXECUTE
                    WORLD_READ             WORLD_EXECUTE)

foreach (SCRIPT ${SCRIPTS})
    ## Remove extensions and make scripts executable ##
    get_filename_component(filename "${SCRIPT}" NAME_WE)

    configure_file(${SCRIPT} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${filename}" @ONLY)

    install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${filename}"
            DESTINATION bin
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                        GROUP_READ             GROUP_EXECUTE
                        WORLD_READ             WORLD_EXECUTE)
endforeach()


### Unit Testing ###
option(build_all_tests "Build all unit tests in the test directory." OFF)

if (build_all_tests)
    add_subdirectory(test)
endif()
