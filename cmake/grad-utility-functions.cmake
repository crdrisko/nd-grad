### Function to create a new test from a predefined naming template ###
function(NDGradNewTest)
    set(options)
    set(one_value_keywords TESTNAME
                           INTERIOR_DIRECTORY)
    set(multi_value_keywords)

    cmake_parse_arguments(TEST_ARGS "${options}" "${one_value_keywords}" "${multi_value_keywords}" ${ARGN})

    add_executable(test${TEST_ARGS_TESTNAME}Functions
                   ${TEST_ARGS_INTERIOR_DIRECTORY}/test${TEST_ARGS_TESTNAME}.cpp ${NEW_SOURCES})

    target_link_libraries(test${TEST_ARGS_TESTNAME}Functions ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    gtest_discover_tests(test${TEST_ARGS_TESTNAME}Functions
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_ARGS_INTERIOR_DIRECTORY})
endfunction()
