// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testSingleRNEMD.cpp - Version 1.0.1
// Author: cdrisko
// Date: 01/22/2020-14:01:34
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = Single

#include <gtest/gtest.h>
#include "../../../src/OpenMD/src/include/rnemdFile.hpp"

using namespace OpenMD::RNEMD;
using namespace Utilities_API::PhysicalQuantities;

RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../src/OpenMD/samples/single.rnemd")};

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testSingleRNEMD, singleFluxTypeCorrectBlockParameters)
{
    RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDBlockParameters() };

    ASSERT_EQ("VSS", rnemdBlock->exchangeMethod);
    ASSERT_EQ("Single", rnemdBlock->fluxType);
    ASSERT_EQ("z", rnemdBlock->privilegedAxis);
    ASSERT_DOUBLE_EQ(1.0, rnemdBlock->exchangeTime.getMagnitude());

    ASSERT_EQ("SPCE_RB_0", rnemdBlock->objectSelection[0]);
    ASSERT_EQ("Na+", rnemdBlock->objectSelection[1]);
    ASSERT_EQ("Cl-", rnemdBlock->objectSelection[2]);

    ASSERT_DOUBLE_EQ(-19.5938, rnemdBlock->selectionA[0].getMagnitude());
    ASSERT_DOUBLE_EQ(19.5938, rnemdBlock->selectionA[1].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdBlock->selectionB[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdBlock->selectionB[1].getMagnitude());

    ASSERT_EQ("Cl-", rnemdBlock->outputSelection[0]);
    ASSERT_EQ("Na+", rnemdBlock->outputSelection[1]);
    ASSERT_EQ("SPCE_RB_0", rnemdBlock->outputSelection[2]);
}

TEST(testSingleRNEMD, singleFluxTypeCorrectInferredParameters)
{
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDInferredParameters() };

    ASSERT_EQ(2, rnemdInferred->numberOfRegions);
    ASSERT_DOUBLE_EQ(39.1876, rnemdInferred->slabWidth.getMagnitude());
    ASSERT_EQ(38, rnemdInferred->dataFieldLabelIndex);
    ASSERT_DOUBLE_EQ(78.37511346, rnemdInferred->boxSize.getMagnitude());
    ASSERT_FALSE(rnemdInferred->hasSelectionB);
}

TEST(testSingleRNEMD, singleFluxTypeCorrectReportParameters)
{
    RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDReportParameters() };

    ASSERT_DOUBLE_EQ(10000002.0, rnemdReport->runningTime.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->kineticFlux.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumFlux[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumFlux[2].getMagnitude());

    ASSERT_DOUBLE_EQ(6.241573e-09, rnemdReport->currentDensity.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->kineticTarget.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumTarget[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumTarget[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->kineticExchange.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->momentumExchange[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->angularMomentumExchange[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->Jz.getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzP[2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0, rnemdReport->JzL[2].getMagnitude());

    ASSERT_DOUBLE_EQ(3.2316331e-09, rnemdReport->Jc_total.getMagnitude());
    ASSERT_DOUBLE_EQ(1.9603903e-09, rnemdReport->Jc_cation.getMagnitude());
    ASSERT_DOUBLE_EQ(1.2712428e-09, rnemdReport->Jc_anion.getMagnitude());

    ASSERT_EQ(5000000, rnemdReport->trialCount);
    ASSERT_EQ(2411203, rnemdReport->failTrialCount);
}

TEST(testSingleRNEMD, singleFluxTypeCorrectRegionSplitting)
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
        std::vector<Concentration> concAnion { individualRegionData->activity[0] };
        std::vector<Concentration> concCation { individualRegionData->activity[1] };
        std::vector<ElectricField> Ez { individualRegionData->electricField[2] };

        std::ofstream outputFile;
        outputFile.open("Single" + std::to_string(region) + ".txt");

        for (size_t j {}; j < z.size(); ++j)
            outputFile << z[j] << " " << temp[j] << " "
                       << concAnion[j] << " " << concCation[j] << " "
                       << Ez[j].convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol",
                            "eV_part")) << std::endl;

        outputFile.close();

        sizeOfRNEMDAxis += z.size();
    }

    ASSERT_EQ(rnemdData->rnemdAxis.size(), sizeOfRNEMDAxis);
}
