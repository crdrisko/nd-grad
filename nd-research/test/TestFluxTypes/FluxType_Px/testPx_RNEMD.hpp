// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testPx_RNEMD.hpp - Version 1.0.0
// Author: cdrisko
// Date: 03/10/2020-07:29:11
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = Px

#ifndef TESTPX_RNEMD_HPP
#define TESTPX_RNEMD_HPP

#include <memory>

#include "../testAssertions.hpp"
#include "../../../RNEMDFileParsing/include/rnemdFile.hpp"

TEST(testPx_RNEMD, Px_FluxTypeCorrectBlockParameters)
{
    OpenMD::RNEMD::RNEMDFilePtr rnemdFile
        = std::make_shared<OpenMD::RNEMD::RNEMDFile>("../../samples/momentum.rnemd");

    OpenMD::RNEMD::RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDParameters()->block };

    assertThat(rnemdBlock->exchangeMethod).hasAValueOf("VSS");
    assertThat(rnemdBlock->fluxType).hasAValueOf("Px");
    assertThat(rnemdBlock->privilegedAxis).hasAValueOf("z");
    assertThat(rnemdBlock->exchangeTime.getMagnitude()).hasAValueNear(2.0);

    assertThat(rnemdBlock->objectSelection[0]).hasAValueOf("Ar");

    assertThat(rnemdBlock->selectionA[0].getMagnitude()).hasAValueNear(-10.0917);
    assertThat(rnemdBlock->selectionA[1].getMagnitude()).hasAValueNear(10.0917);

    assertThat(rnemdBlock->selectionB[0].getMagnitude()).hasAValueNear(90.8257);
    assertThat(rnemdBlock->selectionB[1].getMagnitude()).hasAValueNear(-90.8257);

    assertThat(rnemdBlock->outputSelection[0]).hasAValueOf("Ar");
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectInferredParameters)
{
    OpenMD::RNEMD::RNEMDFilePtr rnemdFile
        = std::make_shared<OpenMD::RNEMD::RNEMDFile>("../../samples/momentum.rnemd");

    OpenMD::RNEMD::RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDParameters()->inferred };

    assertThat(rnemdInferred->numberOfRegions).hasAValueOf(4);
    assertThat(rnemdInferred->slabWidth.getMagnitude()).hasAValueNear(20.1834);
    assertThat(rnemdInferred->dataFieldLabelIndex).hasAValueOf(35);
    assertThat(rnemdInferred->boxSize.getMagnitude()).hasAValueNear(201.83479699);
    assertThat(rnemdInferred->hasSelectionB).isTrue();
    assertThat(rnemdInferred->percentageOfKicksFailed).hasAValueOf(0.0);
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectReportParameters)
{
    OpenMD::RNEMD::RNEMDFilePtr rnemdFile
        = std::make_shared<OpenMD::RNEMD::RNEMDFile>("../../samples/momentum.rnemd");

    OpenMD::RNEMD::RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDParameters()->report };

    assertThat(rnemdReport->runningTime.getMagnitude()).hasAValueNear(10000001.0);


    // Target Fluxes
    assertThat(rnemdReport->kineticFlux.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->momentumFlux[0].getMagnitude()).hasAValueNear(1e-7);
    assertThat(rnemdReport->momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->currentDensity.getMagnitude()).hasAValueNear(0.0);


    // Target One-Time Exchanges
    assertThat(rnemdReport->kineticTarget.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->momentumTarget[0].getMagnitude()).hasAValueNear(0.0012573236);
    assertThat(rnemdReport->momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Exchange Totals
    assertThat(rnemdReport->kineticExchange.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->momentumExchange[0].getMagnitude()).hasAValueNear(6286.618);
    assertThat(rnemdReport->momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Fluxes
    assertThat(rnemdReport->Jz.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->JzP[0].getMagnitude()).hasAValueNear(9.999999e-8);
    assertThat(rnemdReport->JzP[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzP[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->JzL[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzL[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzL[2].getMagnitude()).hasAValueNear(0.0);


    // Exchange Statistics
    assertThat(rnemdReport->trialCount).hasAValueOf(5000000);
    assertThat(rnemdReport->failTrialCount).hasAValueOf(0);
}

#endif
