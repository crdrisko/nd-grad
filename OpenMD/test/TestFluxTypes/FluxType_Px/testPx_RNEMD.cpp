// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testPx_RNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/28/2020-12:30:00
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = Px

#include <fstream>
#include "../testAssertions.hpp"

using namespace OpenMD::RNEMD;
using namespace Utilities_API::PhysicalQuantities;

RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../rnemd/samples/momentum.rnemd")};

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectBlockParameters)
{
    RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDBlockParameters() };

    assertThat(rnemdFile, rnemdBlock->exchangeMethod).hasAValueOf("VSS");
    assertThat(rnemdFile, rnemdBlock->fluxType).hasAValueOf("Px");
    assertThat(rnemdFile, rnemdBlock->privilegedAxis).hasAValueOf("z");
    assertThat(rnemdFile, rnemdBlock->exchangeTime.getMagnitude()).hasAValueNear(2.0);

    assertThat(rnemdFile, rnemdBlock->objectSelection[0]).hasAValueOf("Ar");

    assertThat(rnemdFile, rnemdBlock->selectionA[0].getMagnitude()).hasAValueNear(-10.0917);
    assertThat(rnemdFile, rnemdBlock->selectionA[1].getMagnitude()).hasAValueNear(10.0917);

    assertThat(rnemdFile, rnemdBlock->selectionB[0].getMagnitude()).hasAValueNear(90.8257);
    assertThat(rnemdFile, rnemdBlock->selectionB[1].getMagnitude()).hasAValueNear(-90.8257);

    assertThat(rnemdFile, rnemdBlock->outputSelection[0]).hasAValueOf("Ar");
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectInferredParameters)
{
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDInferredParameters() };

    assertThat(rnemdFile, rnemdInferred->numberOfRegions).hasAValueOf(4);
    assertThat(rnemdFile, rnemdInferred->slabWidth.getMagnitude()).hasAValueNear(20.1834);
    assertThat(rnemdFile, rnemdInferred->dataFieldLabelIndex).hasAValueOf(35);
    assertThat(rnemdFile, rnemdInferred->boxSize.getMagnitude()).hasAValueNear(201.83479699);
    assertThat(rnemdFile, rnemdInferred->hasSelectionB).isTrue();
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectReportParameters)
{
    RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDReportParameters() };

    assertThat(rnemdFile, rnemdReport->runningTime.getMagnitude()).hasAValueNear(10000001.0);


    // Target Fluxes
    assertThat(rnemdFile, rnemdReport->kineticFlux.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->momentumFlux[0].getMagnitude()).hasAValueNear(1e-7);
    assertThat(rnemdFile, rnemdReport->momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->currentDensity.getMagnitude()).hasAValueNear(0.0);


    // Target One-Time Exchanges
    assertThat(rnemdFile, rnemdReport->kineticTarget.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->momentumTarget[0].getMagnitude()).hasAValueNear(0.0012573236);
    assertThat(rnemdFile, rnemdReport->momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Exchange Totals
    assertThat(rnemdFile, rnemdReport->kineticExchange.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->momentumExchange[0].getMagnitude()).hasAValueNear(6286.618);
    assertThat(rnemdFile, rnemdReport->momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Fluxes
    assertThat(rnemdFile, rnemdReport->Jz.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->JzP[0].getMagnitude()).hasAValueNear(9.999999e-8);
    assertThat(rnemdFile, rnemdReport->JzP[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->JzP[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->JzL[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->JzL[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->JzL[2].getMagnitude()).hasAValueNear(0.0);


    // Exchange Statistics
    assertThat(rnemdFile, rnemdReport->trialCount).hasAValueOf(5000000);
    assertThat(rnemdFile, rnemdReport->failTrialCount).hasAValueOf(0);
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectSplitting)
{
    int sizeOfRNEMDAxis {};
    RNEMDDataPtr rnemdData { rnemdFile->getAllDataFromFile() };

    std::vector<RNEMDRegionPtr> rnemdRegionData { rnemdFile->getRNEMDRegions() };
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDInferredParameters() };

    // Test Correct Region Specific Data
    for (int region {1}; region <= rnemdInferred->numberOfRegions; ++region)
    {
        RNEMDDataPtr individualRegionData { rnemdRegionData[region - 1]->getRegionSpecificData() };

        if (region == 1)
            rnemdRegionData[0]->makeFirstRegionContinuous(rnemdInferred->boxSize);

        std::vector<Length> z { individualRegionData->rnemdAxis };
        std::vector<Temperature> temp { individualRegionData->temperature };
        std::array<std::vector<Velocity>, 3> velocity { individualRegionData->velocity };
        std::vector<MassDensity> density { individualRegionData->density };

        std::ofstream outputFile;
        outputFile.open("Momentum" + std::to_string(region) + ".txt");

        for (size_t j {}; j < z.size(); ++j)
            outputFile << z[j] << " " << temp[j] << " "
                       << velocity[0][j] << " " << velocity[1][j] << " "
                       << velocity[2][j] << " " << density[j] << std::endl;

        outputFile.close();

        sizeOfRNEMDAxis += z.size();
    }

    ASSERT_EQ(rnemdData->rnemdAxis.size(), sizeOfRNEMDAxis);
}
