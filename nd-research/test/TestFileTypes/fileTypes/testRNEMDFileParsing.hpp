// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testRNEMDFileParsing.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/14/2020-16:28:44
// Description: Provides ~100% unit test coverage over the RNEMDFile class and functions

#ifndef ND_RESEARCH_TESTRNEMDFILEPARSING_HPP
#define ND_RESEARCH_TESTRNEMDFILEPARSING_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../../testAssertions.hpp"
#include "../../../src/fileTypes/rnemdFiles/rnemdFile.hpp"

namespace ND_Research
{
    GTEST_TEST(testRNEMDFileParsing, correctBlockParameters)
    {
        RNEMDFile rnemdFile {"../../samples/double.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->block.exchangeMethod).hasAValueOf("VSS");
        assertThat(rnemdParameters->block.fluxType).hasAValueOf("Current");
        assertThat(rnemdParameters->block.privilegedAxis).hasAValueOf("z");
        assertThat(rnemdParameters->block.exchangeTime.getMagnitude()).hasAValueNear(2.0);

        assertThat(rnemdParameters->block.objectSelection[0]).hasAValueOf("SPCE_RB_0");
        assertThat(rnemdParameters->block.objectSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.objectSelection[2]).hasAValueOf("Cl-");

        assertThat(rnemdParameters->block.selectionA[0].getMagnitude()).hasAValueNear(-8.0);
        assertThat(rnemdParameters->block.selectionA[1].getMagnitude()).hasAValueNear(8.0);

        assertThat(rnemdParameters->block.selectionB[0].getMagnitude()).hasAValueNear(31.1876);
        assertThat(rnemdParameters->block.selectionB[1].getMagnitude()).hasAValueNear(-31.1876);

        assertThat(rnemdParameters->block.outputSelection[0]).hasAValueOf("Cl-");
        assertThat(rnemdParameters->block.outputSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.outputSelection[2]).hasAValueOf("SPCE_RB_0");
    }

    GTEST_TEST(testRNEMDFileParsing, correctReportParameters)
    {
        RNEMDFile rnemdFile {"../../samples/double.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->report.runningTime.getMagnitude()).hasAValueNear(10000002.0);


        // Target Fluxes
        assertThat(rnemdParameters->report.kineticFlux.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.currentDensity.getMagnitude()).hasAValueNear(6.241573e-09);


        // Target One-Time Exchanges
        assertThat(rnemdParameters->report.kineticTarget.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumTarget[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


        // Actual Exchange Totals
        assertThat(rnemdParameters->report.kineticExchange.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumExchange[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


        // Actual Fluxes
        assertThat(rnemdParameters->report.Jz.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.JzP[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzP[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzP[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.JzL[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzL[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzL[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.Jc_total.getMagnitude()).hasAValueNear(4.2855502e-09);
        assertThat(rnemdParameters->report.Jc_cation.getMagnitude()).hasAValueNear(2.5987457e-09);
        assertThat(rnemdParameters->report.Jc_anion.getMagnitude()).hasAValueNear(1.6868045e-09);


        // Exchange Statistics
        assertThat(rnemdParameters->report.trialCount).hasAValueOf(5000000);
        assertThat(rnemdParameters->report.failTrialCount).hasAValueOf(1566931);
    }

    GTEST_TEST(testRNEMDFileParsing, correctInferredParameters)
    {
        RNEMDFile rnemdFile {"../../samples/double.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->inferred.numberOfRegions).hasAValueOf(4);
        assertThat(rnemdParameters->inferred.slabWidth.getMagnitude()).hasAValueNear(16.0);
        assertThat(rnemdParameters->inferred.dataFieldLabelIndex).hasAValueOf(38);
        assertThat(rnemdParameters->inferred.boxSize.getMagnitude()).hasAValueNear(78.37511346);
        assertThat(rnemdParameters->inferred.hasSelectionB).isTrue();
        assertThat(rnemdParameters->inferred.percentageOfKicksFailed).hasAValueOf(31.33862);
    }

    GTEST_TEST(testRNEMDFileParsing, incorrectInternalFileDataThrowsExceptions)
    {
        ASSERT_DEATH(
        {
            RNEMDFile rnemdFile {"../../scripts/equilibrator.sh"};
        }, "ND-Research Fatal Error:\n\tCould not convert a string value from the file into parameter type using:");
    }

    GTEST_TEST(testRNEMDFileParsing, componentsOfTheRNEMDFileNameAreCorrect)
    {
        RNEMDFile rnemdFile {"../../samples/double.rnemd"};

        assertThat(rnemdFile.getFileName().getFileExtension()).hasAValueOf("rnemd");
        assertThat(rnemdFile.getFileName().getBaseFileName()).hasAValueOf("double.rnemd");
        assertThat(rnemdFile.getFileName().getRelativePathToFile()).hasAValueOf("../../samples");
        assertThat(rnemdFile.getFileName().getFullFileName()).hasAValueOf("../../samples/double.rnemd");
    }

    GTEST_TEST(testRNEMDFileParsing, allDataFieldsAreParsedCorrectly)
    {
        Utilities_API::Files::TextFile actualFile {"../../samples/double.rnemd"};
        std::vector< std::vector<std::string> > actualData {actualFile.getSuperDataVector()};

        RNEMDFile rnemdFile {"../../samples/double.rnemd"};
        RNEMDDataPtr rnemdData {rnemdFile.getAllDataFromFile()};

        for (std::size_t i {}; i < actualData[0].size(); ++i)
        {
            ASSERT_DOUBLE_EQ( rnemdData->rnemdAxis[i].getMagnitude(), std::stold(actualData[i][0]) );
            ASSERT_DOUBLE_EQ( rnemdData->temperature[i].getMagnitude(), std::stold(actualData[i][1]) );
            ASSERT_DOUBLE_EQ( rnemdData->density[i].getMagnitude(), std::stold(actualData[i][5]) );
            ASSERT_DOUBLE_EQ( rnemdData->activity[0][i].getMagnitude(), std::stold(actualData[i][6]) );
            ASSERT_DOUBLE_EQ( rnemdData->activity[1][i].getMagnitude(), std::stold(actualData[i][7]) );
            ASSERT_DOUBLE_EQ( rnemdData->electricPotential[i].getMagnitude(), std::stold(actualData[i][11]) );

            for (std::size_t j {}; j < 3; ++j)
            {
                ASSERT_DOUBLE_EQ( rnemdData->velocity[j][i].getMagnitude(), std::stold(actualData[i][2 + j]) );
                ASSERT_DOUBLE_EQ( rnemdData->electricField[j][i].getMagnitude(), std::stold(actualData[i][8 + j]) );
            }
        }
    }
}

#endif
