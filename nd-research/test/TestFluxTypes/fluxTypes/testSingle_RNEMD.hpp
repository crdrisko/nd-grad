// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testSingle_RNEMD.hpp - Version 1.0.0
// Author: cdrisko
// Date: 03/10/2020-07:29:11
// Description: Provides ~100% unit test coverage over all parameter parsing functions for FluxType = Single

#ifndef ND_RESEARCH_TESTSINGLE_RNEMD_HPP
#define ND_RESEARCH_TESTSINGLE_RNEMD_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../../testAssertions.hpp"
#include "../../../src/fileTypes/rnemdFiles/rnemdFile.hpp"

namespace ND_Research
{
    GTEST_TEST(testSingle_RNEMD, correctBlockParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/single.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->block.exchangeMethod).hasAValueOf("VSS");
        assertThat(rnemdParameters->block.fluxType).hasAValueOf("Single");
        assertThat(rnemdParameters->block.privilegedAxis).hasAValueOf('z');
        assertThat(rnemdParameters->block.exchangeTime.getMagnitude()).hasAValueNear(2.0);

        assertThat(rnemdParameters->block.objectSelection[0]).hasAValueOf("SPCE_RB_0");
        assertThat(rnemdParameters->block.objectSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.objectSelection[2]).hasAValueOf("Cl-");

        assertThat(rnemdParameters->block.selectionA[0].getMagnitude()).hasAValueNear(-19.5938);
        assertThat(rnemdParameters->block.selectionA[1].getMagnitude()).hasAValueNear(19.5938);

        assertThat(rnemdParameters->block.selectionB[0].getMagnitude()).hasAValueNear(0.0);
        assertThat(rnemdParameters->block.selectionB[1].getMagnitude()).hasAValueNear(0.0);

        assertThat(rnemdParameters->block.outputSelection[0]).hasAValueOf("Cl-");
        assertThat(rnemdParameters->block.outputSelection[1]).hasAValueOf("Na+");
        assertThat(rnemdParameters->block.outputSelection[2]).hasAValueOf("SPCE_RB_0");
    }

    GTEST_TEST(testSingle_RNEMD, correctReportParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/single.rnemd"};
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

        assertThat(rnemdParameters->report.Jc_total.getMagnitude()).hasAValueNear(3.2316331e-09);
        assertThat(rnemdParameters->report.Jc_cation.getMagnitude()).hasAValueNear(1.9603903e-09);
        assertThat(rnemdParameters->report.Jc_anion.getMagnitude()).hasAValueNear(1.2712428e-09);


        // Exchange Statistics
        assertThat(rnemdParameters->report.trialCount).hasAValueOf(5000000);
        assertThat(rnemdParameters->report.failTrialCount).hasAValueOf(2411203);
    }

    GTEST_TEST(testSingle_RNEMD, correctInferredParameters)
    {
        RNEMDFile rnemdFile {"../../samples/rnemd/single.rnemd"};
        RNEMDParametersPtr rnemdParameters {rnemdFile.getRNEMDParameters()};

        assertThat(rnemdParameters->inferred.numberOfRegions).hasAValueOf(2);
        assertThat(rnemdParameters->inferred.slabWidth.getMagnitude()).hasAValueNear(39.1876);
        assertThat(rnemdParameters->inferred.dataFieldLabelIndex).hasAValueOf(38);
        assertThat(rnemdParameters->inferred.boxSize.getMagnitude()).hasAValueNear(78.37511346);
        assertThat(rnemdParameters->inferred.hasSelectionB).isFalse();
        assertThat(rnemdParameters->inferred.percentageOfKicksFailed).hasAValueOf(48.22406);
    }

    GTEST_TEST(testSingle_RNEMD, allDataFieldsAreParsedCorrectly)
    {
        Utilities_API::Files::TextFile actualFile {"../../samples/rnemd/single.rnemd"};
        std::vector<std::vector<std::string>> actualData {actualFile.getSuperDataVector()};

        RNEMDFile rnemdFile {"../../samples/rnemd/single.rnemd"};
        RNEMDDataPtr rnemdData {rnemdFile.getRNEMDData()};

        for (std::size_t i {}; i < actualData[0].size(); ++i)
        {
            assertThat(rnemdData->rnemdAxis[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][0]) );
            assertThat(rnemdData->temperature[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][1]) );
            assertThat(rnemdData->density[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][5]) );
            assertThat(rnemdData->activity[0][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][6]) );
            assertThat(rnemdData->activity[1][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][7]) );
            assertThat(rnemdData->electricPotential[i].getMagnitude()).hasAValueNear( std::stold(actualData[i][11]) );

            for (std::size_t j {}; j < 3; ++j)
            {
                assertThat(rnemdData->velocity[j][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][2 + j]) );
                assertThat(rnemdData->electricField[j][i].getMagnitude()).hasAValueNear( std::stold(actualData[i][8 + j]) );
            }
        }
    }
}

#endif
