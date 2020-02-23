// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testCurrent_RNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/22/2020-14:01:49
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = Current

#include "../testAssertions.hpp"
#include "../../../rnemd/RNEMDFileParsing/include/rnemdFile.hpp"

using namespace OpenMD::RNEMD;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testCurrent_RNEMD, currentFluxTypeCorrectBlockParameters)
{
    RNEMDFilePtr rnemdFile { std::make_shared<RNEMDFile>("../../../rnemd/samples/double.rnemd") };
    RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDParameters()->block };

    assertThat(rnemdBlock->exchangeMethod).hasAValueOf("VSS");
    assertThat(rnemdBlock->fluxType).hasAValueOf("Current");
    assertThat(rnemdBlock->privilegedAxis).hasAValueOf("z");
    assertThat(rnemdBlock->exchangeTime.getMagnitude()).hasAValueNear(2.0);

    assertThat(rnemdBlock->objectSelection[0]).hasAValueOf("SPCE_RB_0");
    assertThat(rnemdBlock->objectSelection[1]).hasAValueOf("Na+");
    assertThat(rnemdBlock->objectSelection[2]).hasAValueOf("Cl-");

    assertThat(rnemdBlock->selectionA[0].getMagnitude()).hasAValueNear(-8.0);
    assertThat(rnemdBlock->selectionA[1].getMagnitude()).hasAValueNear(8.0);

    assertThat(rnemdBlock->selectionB[0].getMagnitude()).hasAValueNear(31.1876);
    assertThat(rnemdBlock->selectionB[1].getMagnitude()).hasAValueNear(-31.1876);

    assertThat(rnemdBlock->outputSelection[0]).hasAValueOf("Cl-");
    assertThat(rnemdBlock->outputSelection[1]).hasAValueOf("Na+");
    assertThat(rnemdBlock->outputSelection[2]).hasAValueOf("SPCE_RB_0");
}

TEST(testCurrent_RNEMD, currentFluxTypeCorrectInferredParameters)
{
    RNEMDFilePtr rnemdFile { std::make_shared<RNEMDFile>("../../../rnemd/samples/double.rnemd") };
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDParameters()->inferred };

    assertThat(rnemdInferred->numberOfRegions).hasAValueOf(4);
    assertThat(rnemdInferred->slabWidth.getMagnitude()).hasAValueNear(16.0);
    assertThat(rnemdInferred->dataFieldLabelIndex).hasAValueOf(38);
    assertThat(rnemdInferred->boxSize.getMagnitude()).hasAValueNear(78.37511346);
    assertThat(rnemdInferred->hasSelectionB).isTrue();
}

TEST(testCurrent_RNEMD, currentFluxTypeCorrectReportParameters)
{
    RNEMDFilePtr rnemdFile { std::make_shared<RNEMDFile>("../../../rnemd/samples/double.rnemd") };
    RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDParameters()->report };

    assertThat(rnemdReport->runningTime.getMagnitude()).hasAValueNear(10000002.0);


    // Target Fluxes
    assertThat(rnemdReport->kineticFlux.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->momentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->currentDensity.getMagnitude()).hasAValueNear(6.241573e-09);


    // Target One-Time Exchanges
    assertThat(rnemdReport->kineticTarget.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->momentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Exchange Totals
    assertThat(rnemdReport->kineticExchange.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->momentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Fluxes
    assertThat(rnemdReport->Jz.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->JzP[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzP[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzP[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->JzL[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzL[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzL[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->Jc_total.getMagnitude()).hasAValueNear(4.2855502e-09);
    assertThat(rnemdReport->Jc_cation.getMagnitude()).hasAValueNear(2.5987457e-09);
    assertThat(rnemdReport->Jc_anion.getMagnitude()).hasAValueNear(1.6868045e-09);


    // Exchange Statistics
    assertThat(rnemdReport->trialCount).hasAValueOf(5000000);
    assertThat(rnemdReport->failTrialCount).hasAValueOf(1566931);
}
