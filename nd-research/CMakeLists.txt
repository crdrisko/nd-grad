### Files / Directories ###
if (NOT research_exclude_scripts)
    set(SCRIPTS
        scripts/afsInit.sh
        scripts/equilibrator.sh
        scripts/groupSubmit.sh
        scripts/saltWaterBoxer.sh)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/bin
    CACHE PATH
    "Single directory for all executables.")


### Libraries / Executables ###
add_executable(kirkwoodBuffAnalysis src/applications/emdAnalysis/kirkwoodBuffAnalysis.cpp)
add_executable(onsagerAnalysis      src/applications/emdAnalysis/onsagerAnalysis.cpp)
add_executable(rcorrAnalysis        src/applications/emdAnalysis/rcorrAnalysis.cpp)

# add_executable(soretEffects         src/applications/spf-rnemd/soretEffects.cpp src/fileTypes/rnemdFiles/rnemdFile.cpp)
add_executable(spfFitting           src/applications/spf-rnemd/spfFitting.cpp src/fileTypes/rnemdFiles/rnemdFile.cpp)
add_executable(stitchRNEMD          src/applications/spf-rnemd/stitchRNEMD.cpp src/fileTypes/rnemdFiles/rnemdFile.cpp)
add_executable(thermalProfile       src/applications/spf-rnemd/thermalProfile.cpp src/fileTypes/rnemdFiles/rnemdFile.cpp)


### Installation ###
install(FILES src/fileTypes/rnemdFiles/rnemdFile.hpp src/fileTypes/rnemdFiles/rnemdParameters.hpp
        DESTINATION include/nd-grad)

install(FILES src/fileTypes/emdFiles/emdFile.hpp
        DESTINATION include/nd-grad)

install(TARGETS spfFitting stitchRNEMD thermalProfile kirkwoodBuffAnalysis onsagerAnalysis rcorrAnalysis
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ             GROUP_EXECUTE
                    WORLD_READ             WORLD_EXECUTE)

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
                               REPOSITORY "https://github.com/google/googletest.git"
                               TAG main)

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
