// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testLx_RNEMD.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/29/2020-08:36:59
// Description: Provides ~100% unit test coverage over all parameter parsing functions for FluxType = Lx

#ifndef ND_RESEARCH_TESTLX_RNEMD_HPP
#define ND_RESEARCH_TESTLX_RNEMD_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../../testAssertions.hpp"
#include "../../../src/fileTypes/rnemdFiles/rnemdFile.hpp"

namespace ND_Research
{
    GTEST_TEST(testLx_RNEMD, correctBlockParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/angularMomentum.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->block.exchangeMethod).hasAValueOf("VSS");
        assertThat(rnemdParameters->block.fluxType).hasAValueOf("Lx");
        assertThat(rnemdParameters->block.privilegedAxis).hasAValueOf('R');
        assertThat(rnemdParameters->block.exchangeTime.getMagnitude()).hasAValueNear(2.0);

        assertThat(rnemdParameters->block.objectSelection[0]).hasAValueOf("SPCE_RB_0");
        assertThat(rnemdParameters->block.objectSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.objectSelection[2]).hasAValueOf("Cl-");

        assertThat(rnemdParameters->block.selectionA[0].getMagnitude()).hasAValueNear(11.9867);

        assertThat(rnemdParameters->block.outputSelection[0]).hasAValueOf("Cl-");
        assertThat(rnemdParameters->block.outputSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.outputSelection[2]).hasAValueOf("SPCE_RB_0");
    }

    GTEST_TEST(testLx_RNEMD, correctReportParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/angularMomentum.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->report.runningTime.getMagnitude()).hasAValueNear(36960.0);


        // Target Fluxes
        assertThat(rnemdParameters->report.kineticFlux.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumFlux[0].getMagnitude()).hasAValueNear(100.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.currentDensity.getMagnitude()).hasAValueNear(0.0);


        // Target One-Time Exchanges
        assertThat(rnemdParameters->report.kineticTarget.getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.momentumTarget[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumTarget[0].getMagnitude()).hasAValueNear(361108.16);
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
        assertThat(rnemdParameters->report.trialCount).hasAValueOf(18480);
        assertThat(rnemdParameters->report.failTrialCount).hasAValueOf(18480);
    }

    GTEST_TEST(testLx_RNEMD, correctInferredParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/angularMomentum.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->inferred.numberOfRegions).hasAValueOf(2);
        assertThat(rnemdParameters->inferred.slabWidth.getMagnitude()).hasAValueNear(11.9867);
        assertThat(rnemdParameters->inferred.dataFieldLabelIndex).hasAValueOf(34);
        assertThat(rnemdParameters->inferred.boxSize.getMagnitude()).hasAValueNear(160.0);
        assertThat(rnemdParameters->inferred.hasSelectionB).isFalse();
        assertThat(rnemdParameters->inferred.percentageOfKicksFailed).hasAValueOf(100.0);
    }

    GTEST_TEST(testLx_RNEMD, allDataFieldsAreParsedCorrectly)
    {
        Utilities_API::Files::TextFile actualFile {"../../samples/rnemd/angularMomentum.rnemd"};
        std::vector<std::vector<std::string>> actualData {actualFile.getSuperDataVector()};

        RNEMDFile rnemdFile {"../../samples/rnemd/angularMomentum.rnemd"};
        RNEMDDataPtr rnemdData {rnemdFile.getRNEMDData()};

        for (std::size_t i {}; i < actualData[0].size(); ++i)
        {
            assertThat(rnemdData->rnemdAxis[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][0]) );

            for (std::size_t j {}; j < 3; ++j)
                assertThat(rnemdData->angularVelocity[j][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][1 + j]) );
        }
    }
}

#endif
