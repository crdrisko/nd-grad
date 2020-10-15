### Files / Directories ###
# set(RNEMD_FILE_PARSING_SOURCES
#     RNEMDFileParsing/src/rnemdFile.cpp
#     RNEMDFileParsing/src/rnemdRegion.cpp)

# set(CHARGED_RNEMD_SOURCES
#     ChargedRNEMD/src/chargedRNEMD.cpp
#     ChargedRNEMD/src/chargedRNEMDAnalysisMethod.cpp
#     ChargedRNEMD/src/regionFitting.cpp
#     ChargedRNEMD/src/regionDifference.cpp)

# set(UTILITY_SOURCES
#     src/utilities/dataFields.cpp)

# set(FILETYPE_SOURCES
#     src/fileTypes/rnemdFiles/rnemdFile.cpp
#     src/fileTypes/xyzFiles/xyzFile.cpp)

# set(SHIFTXYZ_SOURCES
#     src/applications/shiftXYZ/shiftXYZ.cpp
#     src/applications/shiftXYZ/xyzFile.cpp)

if (NOT research_exclude_scripts)
    set(SCRIPTS
        scripts/afsInit.sh
        scripts/equilibrator.sh
        scripts/groupSubmit.sh
        scripts/saltWaterBoxer.sh
        src/applications/chargedRNEMD/scripts/plotOptimizationAnalysis.py
        src/applications/chargedRNEMD/scripts/findConcentration.py)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single directory for all executables.")


### Libraries / Executables ###
# add_executable(chargedRNEMD ${CHARGED_RNEMD_SOURCES} ${RNEMD_FILE_PARSING_SOURCES})
# add_executable(shiftXYZ ${SHIFTXYZ_SOURCES})


### Installation ###
# install(TARGETS chargedRNEMD shiftXYZ
#         DESTINATION bin
#         PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
#                     GROUP_READ             GROUP_EXECUTE
#                     WORLD_READ             WORLD_EXECUTE)

if (NOT research_exclude_scripts)
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
endif()


### Unit Testing ###
if (grad_build_tests OR research_build_tests)
    find_package(GTest)
    find_package(Threads)

    if (NOT ${GTest_FOUND})
        ## If googletest isn't installed or can't be found, download it from github ##
        NDGradExternalDownload(PROJECT googletest
                               REPOSITORY "https://github.com/google/googletest.git")

        set(GTEST_LIBRARIES gtest)
        set(GTEST_INCLUDE_DIRS "${gtest_SOURCE_DIR}/include")
    endif()

    include_directories(${GTEST_INCLUDE_DIRS})

    include(CTest)
    include(GoogleTest)

    enable_testing()

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/tests)

    # add_subdirectory(test)
    # add_subdirectory(cmake/Testing ${PROJECT_BINARY_DIR}/Testing)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
endif()
