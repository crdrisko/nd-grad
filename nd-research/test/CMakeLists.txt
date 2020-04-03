### Unit Testing ###
include(CTest)
include(GoogleTest)

enable_testing()


### Functions ###
function(newTest)
    set(options)
    set(one_value_keywords TESTNAME
                           INTERIOR_DIRECTORY)
    set(multi_value_keywords)

    cmake_parse_arguments(TEST_ARGS "${options}" "${one_value_keywords}" "${multi_value_keywords}" ${ARGN})

    add_executable(test${TEST_ARGS_TESTNAME}Functions
                   ${TEST_ARGS_INTERIOR_DIRECTORY}/test${TEST_ARGS_TESTNAME}.cpp ${NEW_SOURCES})

    target_link_libraries(test${TEST_ARGS_TESTNAME}Functions ${GTEST_LIBRARIES})

    gtest_discover_tests(test${TEST_ARGS_TESTNAME}Functions
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_ARGS_INTERIOR_DIRECTORY})
endfunction()


### ShiftXYZ Tests ###
set(NEW_SOURCES ../ShiftXYZ/src/xyzFile.cpp)

newTest(TESTNAME ShiftXYZ
        INTERIOR_DIRECTORY TestShiftXYZ)


### RNEMDFileParsing Tests ###
unset(NEW_SOURCES)

foreach (FILE ${RNEMD_FILE_PARSING_SOURCES})
    list(APPEND NEW_SOURCES ../${FILE})
endforeach()

newTest(TESTNAME AllFluxTypes
        INTERIOR_DIRECTORY TestFluxTypes)

newTest(TESTNAME RegionSplitting
    INTERIOR_DIRECTORY TestRNEMDRegions)


### ChargedRNEMD Tests ###
foreach (FILE ${CHARGED_RNEMD_SOURCES})
    if (NOT ${FILE} EQUAL ChargedRNEMD/src/chargedRNEMD.cpp)
        list(APPEND ${NEW_SOURCES} ../${FILE})
    endif()
endforeach()

newTest(TESTNAME ChargedRNEMDParameters
        INTERIOR_DIRECTORY TestChargedRNEMD)
