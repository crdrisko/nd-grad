### Unit Testing ###
include(CTest)
include(GoogleTest)

enable_testing()

## Function to create a new test based off the pre-defined naming template ##
function (new_test testname interiorDirectory)
    add_executable(test${testname} ${interiorDirectory}/test${testname}.cpp)

    target_link_libraries(test${testname} ${GTEST_LIBRARIES} openmd-plugin ${UTILITIES_API_LIBRARIES})

    gtest_discover_tests(test${testname}
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${interiorDirectory})
endfunction()

## Locate GTest ##
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

## Create all tests ##
# new_test(ChargedRNEMDParameters TestChargedRNEMD)
new_test(CurrentRNEMD TestFluxTypes/FluxType_Current)
new_test(KE_RNEMD TestFluxTypes/FluxType_KE)
new_test(Px_RNEMD TestFluxTypes/FluxType_Px)
new_test(SingleRNEMD TestFluxTypes/FluxType_Single)
