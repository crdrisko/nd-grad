if (NOT ${GTest_FOUND})
    ## Download and unpack googletest at configure time ##
    configure_file(../cmake/CMakeLists.txt.in googletest-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    ## Add googletest directly to our build ##
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                        EXCLUDE_FROM_ALL)

    set(GTEST_LIBRARIES gtest)
    set(GTEST_INCLUDE_DIRS "${gtest_SOURCE_DIR}/include")
    set(GTest_FOUND TRUE)
endif()
