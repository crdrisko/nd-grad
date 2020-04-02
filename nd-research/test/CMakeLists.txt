### Unit Testing ###
include(CTest)
include(GoogleTest)

enable_testing()

## Function to create a new test based off the pre-defined naming template ##
function (new_test testname interiorDirectory)
    add_executable(test${testname} ${interiorDirectory}/test${testname}.cpp ${NEW_SOURCES})

    target_link_libraries(test${testname} ${GTEST_LIBRARIES})

    gtest_discover_tests(test${testname}
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${interiorDirectory})
endfunction()

## ShiftXYZ Tests ##
set(NEW_SOURCES ../ShiftXYZ/src/xyzFile.cpp)

new_test(ShiftXYZ TestShiftXYZ)

## RNEMDFileParsing Tests ##
unset(NEW_SOURCES)

foreach (FILE ${RNEMD_FILE_PARSING_SOURCES})
    list(APPEND NEW_SOURCES ../${FILE})
endforeach()

new_test(AllFluxTypes TestFluxTypes)
new_test(RegionSplitting TestRNEMDRegions)

## ChargedRNEMD Tests ##
foreach (FILE ${CHARGED_RNEMD_SOURCES})
    if (NOT ${FILE} EQUAL ChargedRNEMD/src/chargedRNEMD.cpp)
        list(APPEND ${NEW_SOURCES} ../${FILE})
    endif()
endforeach()

new_test(ChargedRNEMDParameters TestChargedRNEMD)
