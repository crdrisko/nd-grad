### Files / Directories ###
set(SOURCES
    rnemd/RNEMDFileParsing/src/rnemdFile.cpp
    rnemd/RNEMDFileParsing/src/rnemdRegion.cpp)

set(BASH_FILES
    scripts/groupSubmit.sh
    scripts/equilibrator.sh)

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

add_executable(chargedRNEMD rnemd/ChargedRNEMD/src/chargedRNEMD.cpp)
target_link_libraries(chargedRNEMD openmd-plugin)


### Installation ###
install(TARGETS openmd-plugin openmd-plugin-static
        DESTINATION lib)

install(TARGETS chargedRNEMD
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ             GROUP_EXECUTE
                    WORLD_READ             WORLD_EXECUTE)

install(DIRECTORY rnemd/RNEMDFileParsing/include/
        DESTINATION include/nd-research/openmd/RNEMDFileParsing)

install(DIRECTORY rnemd/ChargedRNEMD/include/
        DESTINATION include/nd-research/openmd/ChargedRNEMD)

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
