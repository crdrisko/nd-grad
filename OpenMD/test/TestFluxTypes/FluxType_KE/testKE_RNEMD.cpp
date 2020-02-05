// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testKE_RNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/24/2020-10:07:51
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = KE

#include <gtest/gtest.h>
#include "../../../rnemd/include/rnemdFile.hpp"

using namespace OpenMD::RNEMD;
using namespace Utilities_API::PhysicalQuantities;

RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../rnemd/samples/thermal.rnemd")};

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testKE_RNEMD, KE_FluxTypeCorrectBlockParameters)
{
    RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDBlockParameters() };

    ASSERT_EQ("VSS", rnemdBlock->exchangeMethod);
    ASSERT_EQ("KE", rnemdBlock->fluxType);
    ASSERT_EQ("z", rnemdBlock->privilegedAxis);
    ASSERT_DOUBLE_EQ(1.0, rnemdBlock->exchangeTime.getMagnitude());

    ASSERT_EQ("SPCE_RB_0", rnemdBlock->objectSelection[0]);

    ASSERT_DOUBLE_EQ(-2.0, rnemdBlock->selectionA[0].getMagnitude());
    ASSERT_DOUBLE_EQ(2.0, rnemdBlock->selectionA[1].getMagnitude());

    ASSERT_DOUBLE_EQ(18, rnemdBlock->selectionB[0].getMagnitude());
    ASSERT_DOUBLE_EQ(-18, rnemdBlock->selectionB[1].getMagnitude());

    ASSERT_EQ("SPCE_RB_0", rnemdBlock->outputSelection[0]);
}

TEST(testKE_RNEMD, KE_FluxTypeCorrectInferredParameters)
{
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDInferredParameters() };

    ASSERT_EQ(4, rnemdInferred->numberOfRegions);
    ASSERT_DOUBLE_EQ(4.0, rnemdInferred->slabWidth.getMagnitude());
    ASSERT_EQ(35, rnemdInferred->dataFieldLabelIndex);
    ASSERT_DOUBLE_EQ(40.0, rnemdInferred->boxSize.getMagnitude());
    ASSERT_TRUE(rnemdInferred->hasSelectionB);
}

TEST(testKE_RNEMD, KE_FluxTypeCorrectReportParameters)
{
    RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDReportParameters() };

    ASSERT_DOUBLE_EQ(10000002.0, rnemdReport->runningTime.getMagnitude());

    ASSERT_DOUBLE_EQ(4e-6, rnemdReport->kineticFlux.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->currentDensity.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0030701448, rnemdReport->kineticTarget.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[2].getMagnitude());

    ASSERT_DOUBLE_EQ(15350.724, rnemdReport->kineticExchange.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[2].getMagnitude());

    ASSERT_DOUBLE_EQ(1.9999996e-6, rnemdReport->Jz.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[2].getMagnitude());

    ASSERT_EQ(5000000, rnemdReport->trialCount);
    ASSERT_EQ(0, rnemdReport->failTrialCount);
}

TEST(testKE_RNEMD, KE_FluxTypeCorrectSplitting)
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

        std::ofstream outputFile;
        outputFile.open("Thermal" + std::to_string(region) + ".txt");

        for (size_t j {}; j < z.size(); ++j)
            outputFile << z[j] << " " << temp[j] << std::endl;

        outputFile.close();

        sizeOfRNEMDAxis += z.size();
    }

    ASSERT_EQ(rnemdData->rnemdAxis.size(), sizeOfRNEMDAxis);
}
