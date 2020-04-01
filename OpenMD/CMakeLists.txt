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
    ChargedRNEMD/scripts/plotOptimizationAnalysis.py
    ChargedRNEMD/scripts/findConcentration.py)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single directory for all executables.")


### Libraries / Executables ###
add_executable(chargedRNEMD ${CHARGED_RNEMD_SOURCES} ${RNEMD_FILE_PARSING_SOURCES})
add_executable(shiftXYZ ${SHIFTXYZ_SOURCES})


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
option(nd-research_build_tests "Build all unit tests in the test directory." OFF)

if (nd-research_build_tests)
    find_package(GTest)

    if (NOT ${GTest_FOUND})
        ## If GTest isn't installed or can't be found, look in the external modules file ##
        find_package(GoogleTest)
    endif()

    include_directories(${GTEST_INCLUDE_DIRS})
    add_compile_options(-pthread)

    add_subdirectory(test)
endif()
