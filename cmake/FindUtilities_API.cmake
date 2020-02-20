if (UTILITIES_API_INCLUDE_DIR AND UTILITIES_API_LIBRARIES)
    # in cache already or user-specified
    set(UTILITIES_API_FOUND TRUE)

else()
    if (NOT UTILITIES_API_INCLUDE_DIR)
        find_path(UTILITIES_API_INCLUDE_DIR utilities-api
                  PATHS /usr/include/utilities-api
                        /usr/include
                        /usr/local/include/utilities-api
                        /usr/local/include
                        ~/include/utilities-api
                        ~/include)
    endif()

    if (NOT UTILITIES_API_LIBRARIES)
        find_library(UTILITIES_API_LIBRARIES utilities-api
                     PATHS /usr/lib
                           /usr/local/lib
                           ~/lib)

        if (UTILITIES_API_LIBRARIES)
            message(STATUS "Found Utilities-API: ${UTILITIES_API_LIBRARIES}")
        endif()
    endif()

    if (UTILITIES_API_INCLUDE_DIR AND UTILITIES_API_LIBRARIES)
        set(UTILITIES_API_FOUND TRUE)
    endif()
endif()