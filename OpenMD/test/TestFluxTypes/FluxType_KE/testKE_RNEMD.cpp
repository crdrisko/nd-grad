// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testKE_RNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/24/2020-10:07:51
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = KE

#include "../testAssertions.hpp"
#include "../../../rnemd/RNEMDFileParsing/include/rnemdFile.hpp"

using namespace OpenMD::RNEMD;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testKE_RNEMD, KE_FluxTypeCorrectBlockParameters)
{
    RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../rnemd/samples/thermal.rnemd")};
    RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDParameters()->block };

    assertThat(rnemdBlock->exchangeMethod).hasAValueOf("VSS");
    assertThat(rnemdBlock->fluxType).hasAValueOf("KE");
    assertThat(rnemdBlock->privilegedAxis).hasAValueOf("z");
    assertThat(rnemdBlock->exchangeTime.getMagnitude()).hasAValueNear(1.0);

    assertThat(rnemdBlock->objectSelection[0]).hasAValueOf("SPCE_RB_0");

    assertThat(rnemdBlock->selectionA[0].getMagnitude()).hasAValueNear(-2.0);
    assertThat(rnemdBlock->selectionA[1].getMagnitude()).hasAValueNear(2.0);

    assertThat(rnemdBlock->selectionB[0].getMagnitude()).hasAValueNear(18);
    assertThat(rnemdBlock->selectionB[1].getMagnitude()).hasAValueNear(-18);

    assertThat(rnemdBlock->outputSelection[0]).hasAValueOf("SPCE_RB_0");
}

TEST(testKE_RNEMD, KE_FluxTypeCorrectInferredParameters)
{
    RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../rnemd/samples/thermal.rnemd")};
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDParameters()->inferred };

    assertThat(rnemdInferred->numberOfRegions).hasAValueOf(4);
    assertThat(rnemdInferred->slabWidth.getMagnitude()).hasAValueNear(4.0);
    assertThat(rnemdInferred->dataFieldLabelIndex).hasAValueOf(35);
    assertThat(rnemdInferred->boxSize.getMagnitude()).hasAValueNear(40.0);
    assertThat(rnemdInferred->hasSelectionB).isTrue();
}

TEST(testKE_RNEMD, KE_FluxTypeCorrectReportParameters)
{
    RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../rnemd/samples/thermal.rnemd")};
    RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDParameters()->report };

    assertThat(rnemdReport->runningTime.getMagnitude()).hasAValueNear(10000002.0);


    // Target Fluxes
    assertThat(rnemdReport->kineticFlux.getMagnitude()).hasAValueNear(4e-6);

    assertThat(rnemdReport->momentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->currentDensity.getMagnitude()).hasAValueNear(0.0);


    // Target One-Time Exchanges
    assertThat(rnemdReport->kineticTarget.getMagnitude()).hasAValueNear(0.0030701448);

    assertThat(rnemdReport->momentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Exchange Totals
    assertThat(rnemdReport->kineticExchange.getMagnitude()).hasAValueNear(15350.724);

    assertThat(rnemdReport->momentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Fluxes
    assertThat(rnemdReport->Jz.getMagnitude()).hasAValueNear(1.9999996e-6);

    assertThat(rnemdReport->JzP[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzP[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzP[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdReport->JzL[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzL[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdReport->JzL[2].getMagnitude()).hasAValueNear(0.0);


    // Exchange Statistics
    assertThat(rnemdReport->trialCount).hasAValueOf(5000000);
    assertThat(rnemdReport->failTrialCount).hasAValueOf(0);
}
