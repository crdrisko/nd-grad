### Unit Testing ###
include(CTest)
include(GoogleTest)

enable_testing()


foreach (FILE ${FILETYPE_SOURCES})
    list(APPEND NEW_SOURCES ../${FILE})
endforeach()

newTest(TESTNAME FileTypeParsing
        INTERIOR_DIRECTORY TestFileTypes)

newTest(TESTNAME AllFluxTypes
        INTERIOR_DIRECTORY TestFluxTypes)

# newTest(TESTNAME RegionSplitting
#     INTERIOR_DIRECTORY TestRNEMDRegions)


### ShiftXYZ Tests ###
# set(NEW_SOURCES ../src/applications/shiftXYZ/xyzFile.cpp)

# newTest(TESTNAME ShiftXYZ
#         INTERIOR_DIRECTORY TestShiftXYZ)


# ### ChargedRNEMD Tests ###
# foreach (FILE ${CHARGED_RNEMD_SOURCES})
#     if (NOT ${FILE} EQUAL ChargedRNEMD/src/chargedRNEMD.cpp)
#         list(APPEND ${NEW_SOURCES} ../${FILE})
#     endif()
# endforeach()

# newTest(TESTNAME ChargedRNEMDParameters
#         INTERIOR_DIRECTORY TestChargedRNEMD)
