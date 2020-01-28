// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testPx_RNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/28/2020-12:30:00
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = Px

#include <gtest/gtest.h>
#include "../../../src/OpenMD/src/include/rnemdFile.hpp"

using namespace OpenMD::RNEMD;
using namespace Utilities_API::PhysicalQuantities;

RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../src/OpenMD/samples/momentum.rnemd")};

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectBlockParameters)
{
    RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDBlockParameters() };

    ASSERT_EQ("VSS", rnemdBlock->exchangeMethod);
    ASSERT_EQ("Px", rnemdBlock->fluxType);
    ASSERT_EQ("z", rnemdBlock->privilegedAxis);
    ASSERT_DOUBLE_EQ(2.0, rnemdBlock->exchangeTime.getMagnitude());

    ASSERT_EQ("Ar", rnemdBlock->objectSelection[0]);

    ASSERT_DOUBLE_EQ(-10.0917, rnemdBlock->selectionA[0].getMagnitude());
    ASSERT_DOUBLE_EQ(10.0917, rnemdBlock->selectionA[1].getMagnitude());

    ASSERT_DOUBLE_EQ(90.8257, rnemdBlock->selectionB[0].getMagnitude());
    ASSERT_DOUBLE_EQ(-90.8257, rnemdBlock->selectionB[1].getMagnitude());

    ASSERT_EQ("Ar", rnemdBlock->outputSelection[0]);
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectInferredParameters)
{
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDInferredParameters() };

    ASSERT_EQ(4, rnemdInferred->numberOfRegions);
    ASSERT_DOUBLE_EQ(20.1834, rnemdInferred->slabWidth.getMagnitude());
    ASSERT_EQ(35, rnemdInferred->dataFieldLabelIndex);
    ASSERT_DOUBLE_EQ(201.83479699, rnemdInferred->boxSize.getMagnitude());
    ASSERT_TRUE(rnemdInferred->hasSelectionB);
}

TEST(testPx_RNEMD, Px_FluxTypeCorrectReportParameters)
{
    RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDReportParameters() };

    ASSERT_DOUBLE_EQ(10000001.0, rnemdReport->runningTime.getMagnitude());

    ASSERT_DOUBLE_EQ(0, rnemdReport->kineticFlux.getMagnitude());

    ASSERT_DOUBLE_EQ(1e-7, rnemdReport->momentumFlux[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->currentDensity.getMagnitude());

    ASSERT_DOUBLE_EQ(0, rnemdReport->kineticTarget.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0012573236, rnemdReport->momentumTarget[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->kineticExchange.getMagnitude());

    ASSERT_DOUBLE_EQ(6286.618, rnemdReport->momentumExchange[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->Jz.getMagnitude());

    ASSERT_DOUBLE_EQ(9.999999e-8, rnemdReport->JzP[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[2].getMagnitude());

    ASSERT_EQ(5000000, rnemdReport->trialCount);
    ASSERT_EQ(0, rnemdReport->failTrialCount);
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

