### External Module File for DryPhys ###
if (DRYPHYS_INCLUDE_DIR AND ENGINE2D_INCLUDE_DIR AND ENGINE2D_LIBRARIES)
    ## In cache already or user-specified ##
    set(DryPhys_FOUND TRUE)
else()
    set(DryPhys_FOUND FALSE)

    if (NOT DRYPHYS_INCLUDE_DIR)
        find_path(DRYPHYS_INCLUDE_DIR dryphys
                  PATHS /opt/local/include/dryphys
                        /opt/local/include
                        /usr/include/dryphys
                        /usr/include
                        /usr/local/include/dryphys
                        /usr/local/include
                        ~/include/dryphys
                        ~/include)
    endif()

    if(NOT ENGINE2D_LIBRARIES)
        find_library(ENGINE2D_LIBRARIES engine2d engine2d_gui
                     PATHS  /opt/local/lib
                            /usr/lib
                            /usr/local/lib
                            ~/lib)
    endif()

    if (NOT ENGINE2D_INCLUDE_DIR)
        find_path(ENGINE2D_INCLUDE_DIR engine2d
                  PATHS /opt/local/include/engine2d
                        /opt/local/include
                        /usr/include/engine2d
                        /usr/include
                        /usr/local/include/engine2d
                        /usr/local/include
                        ~/include/engine2d
                        ~/include)
    endif()

    if (DRYPHYS_INCLUDE_DIR AND ENGINE2D_LIBRARIES AND ENGINE2D_INCLUDE_DIR)
        set(DryPhys_FOUND TRUE)
    endif()
endif()
