if (UTILITIES_API_INCLUDE_DIR)
    ## In cache already or user-specified ##
    set(UTILITIES_API_FOUND TRUE)

else()
    set(UTILITIES_API_FOUND FALSE)

    if (NOT UTILITIES_API_INCLUDE_DIR)
        find_path(UTILITIES_API_INCLUDE_DIR utils-api
                  PATHS /usr/include/utils-api
                        /usr/include
                        /usr/local/include/utils-api
                        /usr/local/include
                        ~/include/utils-api
                        ~/include)
    endif()

    if (UTILITIES_API_INCLUDE_DIR)
        set(UTILITIES_API_FOUND TRUE)

    else()
        ## Download and unpack utilities-api at configure time ##
        configure_file(cmake/CMakeLists.txt.in utilities-api-download/CMakeLists.txt)

        execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                        RESULT_VARIABLE result
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/utilities-api-download)
        if(result)
            message(FATAL_ERROR "CMake step for utilities-api failed: ${result}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} --build .
                        RESULT_VARIABLE result
                        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/utilities-api-download)
        if(result)
            message(FATAL_ERROR "Build step for utilities-api failed: ${result}")
        endif()

        ## Add utilities-api directly to our build ##
        add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/utilities-api-src
                         ${CMAKE_CURRENT_BINARY_DIR}/utilities-api-build
                         EXCLUDE_FROM_ALL)

        set(UTILITIES_API_INCLUDE_DIR "${Utilities-API_SOURCE_DIR}/include")
        set(UTILITIES_API_FOUND TRUE)
    endif()
endif()
