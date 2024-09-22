### External Module File for DryPhys ###
if (DryPhys_LIBRARIES)
    ## In cache already or user-specified ##
    set(DryPhys_FOUND TRUE)
else()
    set(DryPhys_FOUND FALSE)

    if (NOT DryPhys_LIBRARIES)
        find_path(DryPhys_LIBRARIES dryphys
                  PATHS /opt/local/include/dryphys
                        /opt/local/include
                        /usr/include/dryphys
                        /usr/include
                        /usr/local/include/dryphys
                        /usr/local/include
                        ~/include/dryphys
                        ~/include)
    endif()

    if (DryPhys_LIBRARIES)
        set(DryPhys_FOUND TRUE)
    endif()
endif()
