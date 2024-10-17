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
if (NOT research_exclude_npgBuilder)
    set(NPGBUILDER_SOURCE src/applications/npgBuilder/engine/engine.cpp
                          src/applications/npgBuilder/engine/entityManager.cpp
                          src/applications/npgBuilder/engine/vec2.cpp)

    set(IMGUI_SOURCE ${imgui_SOURCE_DIR}/imgui_demo.cpp
                     ${imgui_SOURCE_DIR}/imgui_draw.cpp
                     ${imgui_SOURCE_DIR}/imgui_tables.cpp
                     ${imgui_SOURCE_DIR}/imgui_widgets.cpp
                     ${imgui_SOURCE_DIR}/imgui.cpp
                     ${imgui_sfml_SOURCE_DIR}/imgui-SFML.cpp)  

    add_executable(npgBuilder src/applications/npgBuilder/main.cpp ${NPGBUILDER_SOURCE} ${IMGUI_SOURCE})

    target_link_libraries(npgBuilder PRIVATE ImGui-SFML::ImGui-SFML)
endif()

set(RESEARCH_SOURCE src/fzFile.cpp
                    src/rnemdFile.cpp
                    src/xyzFile.cpp)

add_library(research STATIC ${RESEARCH_SOURCE})

add_executable(currentDensityAnalysis src/applications/emdAnalysis/currentDensityAnalysis.cpp)
add_executable(kirkwoodBuffAnalysis   src/applications/emdAnalysis/kirkwoodBuffAnalysis.cpp)
add_executable(onsagerAnalysis        src/applications/emdAnalysis/onsagerAnalysis.cpp)
add_executable(rcorrAnalysis          src/applications/emdAnalysis/rcorrAnalysis.cpp)

add_executable(fzConstraintAnalysis   src/applications/spf-rnemd/fzConstraintAnalysis.cpp src/fzFile.cpp)

add_executable(chargedSPF             src/applications/spf-rnemd/chargedSPF.cpp src/rnemdFile.cpp)
add_executable(membranePermeability   src/applications/spf-rnemd/membranePermeability.cpp src/rnemdFile.cpp)
add_executable(soretEffects           src/applications/spf-rnemd/soretEffects.cpp src/rnemdFile.cpp)
add_executable(spfFitting             src/applications/spf-rnemd/spfFitting.cpp src/rnemdFile.cpp)
add_executable(stitchRNEMD            src/applications/spf-rnemd/stitchRNEMD.cpp src/rnemdFile.cpp)
add_executable(thermalProfile         src/applications/spf-rnemd/thermalProfile.cpp src/rnemdFile.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${NDGrad_BINARY_DIR}/bin)


### Installation ###
install(TARGETS research
        DESTINATION lib)

install(FILES include/rnemdFile.hpp include/rnemdParameters.hpp
        DESTINATION include/nd-grad)

install(FILES include/emdFile.hpp
        DESTINATION include/nd-grad)

install(TARGETS currentDensityAnalysis kirkwoodBuffAnalysis onsagerAnalysis rcorrAnalysis 
                chargedSPF fzConstraintAnalysis membranePermeability soretEffects 
                spfFitting stitchRNEMD thermalProfile
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ             GROUP_EXECUTE
                    WORLD_READ             WORLD_EXECUTE)

if (NOT research_exclude_npgBuilder)
    install(TARGETS npgBuilder
            DESTINATION bin
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                        GROUP_READ             GROUP_EXECUTE
                        WORLD_READ             WORLD_EXECUTE)
endif()

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
