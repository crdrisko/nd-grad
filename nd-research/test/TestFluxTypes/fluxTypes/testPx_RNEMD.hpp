// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testPx_RNEMD.hpp - Version 1.0.0
// Author: cdrisko
// Date: 03/10/2020-07:29:11
// Description: Provides ~100% unit test coverage over all parameter parsing functions for FluxType = Px

#ifndef ND_RESEARCH_TESTPX_RNEMD_HPP
#define ND_RESEARCH_TESTPX_RNEMD_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../../testAssertions.hpp"
#include "../../../src/fileTypes/rnemdFiles/rnemdFile.hpp"

namespace ND_Research
{
    GTEST_TEST(testPx_RNEMD, correctBlockParameters)
    {
        RNEMDFile rnemdFile {"../../samples/momentum.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->block.exchangeMethod).hasAValueOf("VSS");
        assertThat(rnemdParameters->block.fluxType).hasAValueOf("Px");
        assertThat(rnemdParameters->block.privilegedAxis).hasAValueOf("z");
        assertThat(rnemdParameters->block.exchangeTime.getMagnitude()).hasAValueNear(2.0);

        assertThat(rnemdParameters->block.objectSelection[0]).hasAValueOf("Ar");

        assertThat(rnemdParameters->block.selectionA[0].getMagnitude()).hasAValueNear(-10.0917);
        assertThat(rnemdParameters->block.selectionA[1].getMagnitude()).hasAValueNear(10.0917);

        assertThat(rnemdParameters->block.selectionB[0].getMagnitude()).hasAValueNear(90.8257);
        assertThat(rnemdParameters->block.selectionB[1].getMagnitude()).hasAValueNear(-90.8257);

        assertThat(rnemdParameters->block.outputSelection[0]).hasAValueOf("Ar");
    }

    GTEST_TEST(testPx_RNEMD, correctReportParameters)
    {
        RNEMDFile rnemdFile {"../../samples/momentum.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->report.runningTime.getMagnitude()).hasAValueNear(10000001.0);


        // Target Fluxes
        assertThat(rnemdParameters->report.kineticFlux.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumFlux[0].getMagnitude()).hasAValueNear(1e-7);
        assertThat(rnemdParameters->report.momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.currentDensity.getMagnitude()).hasAValueNear(0.0);


        // Target One-Time Exchanges
        assertThat(rnemdParameters->report.kineticTarget.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumTarget[0].getMagnitude()).hasAValueNear(0.0012573236);
        assertThat(rnemdParameters->report.momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


        // Actual Exchange Totals
        assertThat(rnemdParameters->report.kineticExchange.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumExchange[0].getMagnitude()).hasAValueNear(6286.618);
        assertThat(rnemdParameters->report.momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


        // Actual Fluxes
        assertThat(rnemdParameters->report.Jz.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.JzP[0].getMagnitude()).hasAValueNear(9.999999e-8);
        assertThat(rnemdParameters->report.JzP[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzP[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.JzL[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzL[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzL[2].getMagnitude()).hasAValueNear(0.0);


        // Exchange Statistics
        assertThat(rnemdParameters->report.trialCount).hasAValueOf(5000000);
        assertThat(rnemdParameters->report.failTrialCount).hasAValueOf(0);
    }

    GTEST_TEST(testPx_RNEMD, correctInferredParameters)
    {
        RNEMDFile rnemdFile {"../../samples/momentum.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->inferred.numberOfRegions).hasAValueOf(4);
        assertThat(rnemdParameters->inferred.slabWidth.getMagnitude()).hasAValueNear(20.1834);
        assertThat(rnemdParameters->inferred.dataFieldLabelIndex).hasAValueOf(35);
        assertThat(rnemdParameters->inferred.boxSize.getMagnitude()).hasAValueNear(201.83479699);
        assertThat(rnemdParameters->inferred.hasSelectionB).isTrue();
        assertThat(rnemdParameters->inferred.percentageOfKicksFailed).hasAValueOf(0.0);
    }

    GTEST_TEST(testPx_RNEMD, allDataFieldsAreParsedCorrectly)
    {
        Utilities_API::Files::TextFile actualFile {"../../samples/momentum.rnemd"};
        std::vector< std::vector<std::string> > actualData {actualFile.getSuperDataVector()};

        RNEMDFile rnemdFile {"../../samples/momentum.rnemd"};
        RNEMDDataPtr rnemdData {rnemdFile.getAllDataFromFile()};

        for (std::size_t i {}; i < actualData[0].size(); ++i)
        {
            ASSERT_DOUBLE_EQ( rnemdData->rnemdAxis[i].getMagnitude(), std::stold(actualData[i][0]) );
            ASSERT_DOUBLE_EQ( rnemdData->temperature[i].getMagnitude(), std::stold(actualData[i][1]) );
            ASSERT_DOUBLE_EQ( rnemdData->density[i].getMagnitude(), std::stold(actualData[i][5]) );

            for (std::size_t j {}; j < 3; ++j)
                ASSERT_DOUBLE_EQ( rnemdData->velocity[j][i].getMagnitude(), std::stold(actualData[i][2 + j]) );
        }
    }
}

#endif
