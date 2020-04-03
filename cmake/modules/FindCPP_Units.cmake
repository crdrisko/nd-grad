### External Module File for CPP-Units ###
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
    endif()
endif()
