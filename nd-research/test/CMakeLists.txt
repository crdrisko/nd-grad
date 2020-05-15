### Unit Testing ###
include(CTest)
include(GoogleTest)

enable_testing()

## Data Field Parsing ##
foreach (FILE ${UTILITY_SOURCES})
    list(APPEND NEW_SOURCES ../${FILE})
endforeach()

ND_RESEARCH_NewTest(TESTNAME DataFieldParsing
                    INTERIOR_DIRECTORY TestDataFields)

## File Type Parsing ##
foreach (FILE ${FILETYPE_SOURCES})
    list(APPEND NEW_SOURCES ../${FILE})
endforeach()

ND_RESEARCH_NewTest(TESTNAME FileTypeParsing
                    INTERIOR_DIRECTORY TestFileTypes)

ND_RESEARCH_NewTest(TESTNAME AllFluxTypes
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
