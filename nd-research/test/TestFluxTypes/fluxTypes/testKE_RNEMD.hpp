// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testKE_RNEMD.hpp - Version 1.0.0
// Author: cdrisko
// Date: 03/10/2020-07:29:11
// Description: Provides ~100% unit test coverage over all parameter parsing functions for FluxType = KE

#ifndef ND_RESEARCH_TESTKE_RNEMD_HPP
#define ND_RESEARCH_TESTKE_RNEMD_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../../testAssertions.hpp"
#include "../../../src/fileTypes/rnemdFiles/rnemdFile.hpp"

namespace ND_Research
{
    GTEST_TEST(testKE_RNEMD, correctBlockParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/thermal.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->block.exchangeMethod).hasAValueOf("VSS");
        assertThat(rnemdParameters->block.fluxType).hasAValueOf("KE");
        assertThat(rnemdParameters->block.privilegedAxis).hasAValueOf('z');
        assertThat(rnemdParameters->block.exchangeTime.getMagnitude()).hasAValueNear(1.0);

        assertThat(rnemdParameters->block.objectSelection[0]).hasAValueOf("SPCE_RB_0");

        assertThat(rnemdParameters->block.selectionA[0].getMagnitude()).hasAValueNear(-2.0);
        assertThat(rnemdParameters->block.selectionA[1].getMagnitude()).hasAValueNear(2.0);

        assertThat(rnemdParameters->block.selectionB[0].getMagnitude()).hasAValueNear(18.0);
        assertThat(rnemdParameters->block.selectionB[1].getMagnitude()).hasAValueNear(-18.0);

        assertThat(rnemdParameters->block.outputSelection[0]).hasAValueOf("SPCE_RB_0");
    }

    GTEST_TEST(testKE_RNEMD, correctReportParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/thermal.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->report.runningTime.getMagnitude()).hasAValueNear(10000002.0);


        // Target Fluxes
        assertThat(rnemdParameters->report.kineticFlux.getMagnitude()).hasAValueNear(4e-6);

        assertThat(rnemdParameters->report.momentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.currentDensity.getMagnitude()).hasAValueNear(0.0);


        // Target One-Time Exchanges
        assertThat(rnemdParameters->report.kineticTarget.getMagnitude()).hasAValueNear(0.0030701448);

        assertThat(rnemdParameters->report.momentumTarget[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


        // Actual Exchange Totals
        assertThat(rnemdParameters->report.kineticExchange.getMagnitude()).hasAValueNear(15350.724);

        assertThat(rnemdParameters->report.momentumExchange[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


        // Actual Fluxes
        assertThat(rnemdParameters->report.Jz.getMagnitude()).hasAValueNear(1.9999996e-6);

        assertThat(rnemdParameters->report.JzP[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzP[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzP[2].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->report.JzL[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzL[1].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->report.JzL[2].getMagnitude()).hasAValueNear(0.0);


        // Exchange Statistics
        assertThat(rnemdParameters->report.trialCount).hasAValueOf(5000000);
        assertThat(rnemdParameters->report.failTrialCount).hasAValueOf(0);
    }

    GTEST_TEST(testKE_RNEMD, correctInferredParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/thermal.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->inferred.numberOfRegions).hasAValueOf(4);
        assertThat(rnemdParameters->inferred.slabWidth.getMagnitude()).hasAValueNear(4.0);
        assertThat(rnemdParameters->inferred.dataFieldLabelIndex).hasAValueOf(35);
        assertThat(rnemdParameters->inferred.boxSize.getMagnitude()).hasAValueNear(40.0);
        assertThat(rnemdParameters->inferred.hasSelectionB).isTrue();
        assertThat(rnemdParameters->inferred.percentageOfKicksFailed).hasAValueOf(0.0);
    }

    GTEST_TEST(testKE_RNEMD, allDataFieldsAreParsedCorrectly)
    {
        Utilities_API::Files::TextFile actualFile {"../../samples/rnemd/thermal.rnemd"};
        std::vector<std::vector<std::string>> actualData {actualFile.getSuperDataVector()};

        RNEMDFile rnemdFile {"../../samples/rnemd/thermal.rnemd"};
        RNEMDDataPtr rnemdData {rnemdFile.getRNEMDData()};

        for (std::size_t i {}; i < actualData[0].size(); ++i)
        {
            assertThat(rnemdData->rnemdAxis[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][0]) );
            assertThat(rnemdData->temperature[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][1]) );
        }
    }
}

#endif
