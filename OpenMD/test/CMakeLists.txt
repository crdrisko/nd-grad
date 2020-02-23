### Unit Testing ###
include(CTest)
include(GoogleTest)

enable_testing()

## Adjust source code paths to account for different directory ##
foreach (FILE ${RNEMD_FILE_PARSING_SOURCES})
    list(APPEND NEW_RNEMD_FILE_SOURCES ../${FILE})
endforeach()

## Function to create a new test based off the pre-defined naming template ##
function (new_test testname interiorDirectory)
    add_executable(test${testname} ${interiorDirectory}/test${testname}.cpp ${NEW_RNEMD_FILE_SOURCES})

    target_link_libraries(test${testname} ${GTEST_LIBRARIES} ${UTILITIES_API_LIBRARIES})

    gtest_discover_tests(test${testname}
                            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${interiorDirectory})
endfunction()

## Function to create a new test based off the pre-defined naming template for the different fluxtypes ##
function (new_fluxtype_test testname)
    new_test(${testname}_RNEMD TestFluxTypes/FluxType_${testname})
endfunction()

## Locate GTest ##
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${UTILITIES_API_INCLUDE_DIR})

## Create all tests ##
new_fluxtype_test(Current)
new_fluxtype_test(KE)
new_fluxtype_test(Px)
new_fluxtype_test(Single)

new_test(RegionSplitting TestRNEMDRegions)

# new_test(ChargedRNEMDParameters TestChargedRNEMD)
