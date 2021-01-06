// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testNIVS_RNEMD.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/29/2020-08:34:24
// Description: Provides ~100% unit test coverage over all parameter parsing functions for the NIVS method

#ifndef ND_RESEARCH_TESTNIVS_RNEMD_HPP
#define ND_RESEARCH_TESTNIVS_RNEMD_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../../testAssertions.hpp"
#include "../../../src/fileTypes/rnemdFiles/rnemdFile.hpp"

namespace ND_Research
{
    GTEST_TEST(testNIVS_RNEMD, correctBlockParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/nivs.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->block.exchangeMethod).hasAValueOf("NIVS");
        assertThat(rnemdParameters->block.fluxType).hasAValueOf("KE");
        assertThat(rnemdParameters->block.privilegedAxis).hasAValueOf('x');
        assertThat(rnemdParameters->block.exchangeTime.getMagnitude()).hasAValueNear(2.0);

        assertThat(rnemdParameters->block.objectSelection[0]).hasAValueOf("SPCE_RB_0");
        assertThat(rnemdParameters->block.objectSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.objectSelection[2]).hasAValueOf("Cl-");

        assertThat(rnemdParameters->block.selectionA[0].getMagnitude()).hasAValueNear(-8.0);
        assertThat(rnemdParameters->block.selectionA[1].getMagnitude()).hasAValueNear(8.0);

        assertThat(rnemdParameters->block.selectionB[0].getMagnitude()).hasAValueNear(4.24611);
        assertThat(rnemdParameters->block.selectionB[1].getMagnitude()).hasAValueNear(-4.24611);

        assertThat(rnemdParameters->block.outputSelection[0]).hasAValueOf("Cl-");
        assertThat(rnemdParameters->block.outputSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.outputSelection[2]).hasAValueOf("SPCE_RB_0");
    }

    GTEST_TEST(testNIVS_RNEMD, correctReportParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/nivs.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->report.runningTime.getMagnitude()).hasAValueNear(12090.0);


        // Target Fluxes
        assertThat(rnemdParameters->report.kineticFlux.getMagnitude()).hasAValueNear(100);

        assertThat(rnemdParameters->report.momentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.currentDensity.getMagnitude()).hasAValueNear(0.0);


        // Target One-Time Exchanges
        assertThat(rnemdParameters->report.kineticTarget.getMagnitude()).hasAValueNear(767832.3);

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


        // Exchange Statistics
        assertThat(rnemdParameters->report.trialCount).hasAValueOf(6045);
        assertThat(rnemdParameters->report.failTrialCount).hasAValueOf(6045);

        // NIVS Root Checking Statistics
        assertThat(rnemdParameters->report.failRootCount).hasAValueOf(0);
    }

    GTEST_TEST(testNIVS_RNEMD, correctInferredParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/nivs.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->inferred.numberOfRegions).hasAValueOf(4);
        assertThat(rnemdParameters->inferred.slabWidth.getMagnitude()).hasAValueNear(16.0);
        assertThat(rnemdParameters->inferred.dataFieldLabelIndex).hasAValueOf(36);
        assertThat(rnemdParameters->inferred.boxSize.getMagnitude()).hasAValueNear(24.49222339);
        assertThat(rnemdParameters->inferred.hasSelectionB).isTrue();
        assertThat(rnemdParameters->inferred.percentageOfKicksFailed).hasAValueOf(100.0);
    }

    GTEST_TEST(testNIVS_RNEMD, allDataFieldsAreParsedCorrectly)
    {
        Utilities_API::Files::TextFile actualFile {"../../samples/rnemd/nivs.rnemd"};
        std::vector<std::vector<std::string>> actualData {actualFile.getSuperDataVector()};

        RNEMDFile rnemdFile {"../../samples/rnemd/nivs.rnemd"};
        RNEMDDataPtr rnemdData {rnemdFile.getRNEMDData()};

        for (std::size_t i {}; i < actualData[0].size(); ++i)
        {
            assertThat(rnemdData->rnemdAxis[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][0]) );
            assertThat(rnemdData->temperature[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][1]) );
        }
    }
}

#endif
