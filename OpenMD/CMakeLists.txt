### Files / Directories ###
set(RNEMD_FILE_PARSING_SOURCES
    rnemd/RNEMDFileParsing/src/rnemdFile.cpp
    rnemd/RNEMDFileParsing/src/rnemdRegion.cpp)

# set(CHARGED_RNEMD_SOURCES
#     rnemd/ChargedRNEMD/src/chargedRNEMD.cpp
#     rnemd/ChargedRNEMD/src/chargedRNEMDAnalysisMethod.cpp
#     rnemd/ChargedRNEMD/src/regionFitting.cpp
#     rnemd/ChargedRNEMD/src/regionDifference.cpp)

set(BASH_FILES
    scripts/groupSubmit.sh
    scripts/equilibrator.sh)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single directory for all executables.")


### Libraries / Executables ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

find_package(Utilities_API REQUIRED)

# add_executable(chargedRNEMD ${CHARGED_RNEMD_SOURCES})
# target_link_libraries(chargedRNEMD openmd-plugin)


### Installation ###
# install(TARGETS chargedRNEMD
#         DESTINATION bin
#         PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
#                     GROUP_READ             GROUP_EXECUTE
#                     WORLD_READ             WORLD_EXECUTE)

# install(DIRECTORY rnemd/ChargedRNEMD/include/
#         DESTINATION include/nd-research/openmd/ChargedRNEMD)

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
    add_subdirectory(test)
endif()
