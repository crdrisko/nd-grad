if (CPP_UNITS_INCLUDE_DIR)
    ## In cache already or user-specified ##
    set(CPP_UNITS_FOUND TRUE)

else()
    set(CPP_UNITS_FOUND FALSE)

    if (NOT CPP_UNITS_INCLUDE_DIR)
        find_path(CPP_UNITS_INCLUDE_DIR cpp-units
                  PATHS /usr/include/cpp-units
                        /usr/include
                        /usr/local/include/cpp-units
                        /usr/local/include
                        ~/include/cpp-units
                        ~/include)
    endif()

    if (CPP_UNITS_INCLUDE_DIR)
        set(CPP_UNITS_FOUND TRUE)

    else()
        ## Download and unpack cpp-units at configure time ##
        configure_file(cmake/CMakeLists.txt.in cpp-units-download/CMakeLists.txt)

        execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                        RESULT_VARIABLE result
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cpp-units-download)
        if(result)
            message(FATAL_ERROR "CMake step for cpp-units failed: ${result}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} --build .
                        RESULT_VARIABLE result
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cpp-units-download)
        if(result)
            message(FATAL_ERROR "Build step for cpp-units failed: ${result}")
        endif()

        ## Add cpp-units directly to our build ##
        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/cpp-units-src
                         ${CMAKE_CURRENT_BINARY_DIR}/cpp-units-build
                         EXCLUDE_FROM_ALL)

        set(CPP_UNITS_INCLUDE_DIR "${CPP-Units_SOURCE_DIR}/include")
        set(CPP_UNITS_FOUND TRUE)
    endif()
endif()
