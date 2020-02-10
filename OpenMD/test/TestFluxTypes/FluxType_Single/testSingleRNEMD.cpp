// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testSingleRNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/22/2020-14:01:34
// Description: Provides 100% unit test coverage over all parameter parsing functions for FluxType = Single

#include "../testAssertions.hpp"

using namespace OpenMD::RNEMD;
using namespace Utilities_API::PhysicalQuantities;

RNEMDFilePtr rnemdFile {std::make_shared<RNEMDFile>("../../../rnemd/samples/single.rnemd")};

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testSingleRNEMD, singleFluxTypeCorrectBlockParameters)
{
    RNEMDBlockParametersPtr rnemdBlock { rnemdFile->getRNEMDBlockParameters() };

    assertThat(rnemdFile, rnemdBlock->exchangeMethod).hasAValueOf("VSS");
    assertThat(rnemdFile, rnemdBlock->fluxType).hasAValueOf("Single");
    assertThat(rnemdFile, rnemdBlock->privilegedAxis).hasAValueOf("z");
    assertThat(rnemdFile, rnemdBlock->exchangeTime.getMagnitude()).hasAValueNear(2.0);

    assertThat(rnemdFile, rnemdBlock->objectSelection[0]).hasAValueOf("SPCE_RB_0");
    assertThat(rnemdFile, rnemdBlock->objectSelection[1]).hasAValueOf("Na+");
    assertThat(rnemdFile, rnemdBlock->objectSelection[2]).hasAValueOf("Cl-");

    assertThat(rnemdFile, rnemdBlock->selectionA[0].getMagnitude()).hasAValueNear(-19.5938);
    assertThat(rnemdFile, rnemdBlock->selectionA[1].getMagnitude()).hasAValueNear(19.5938);

    assertThat(rnemdFile, rnemdBlock->selectionB[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdBlock->selectionB[1].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdBlock->outputSelection[0]).hasAValueOf("Cl-");
    assertThat(rnemdFile, rnemdBlock->outputSelection[1]).hasAValueOf("Na+");
    assertThat(rnemdFile, rnemdBlock->outputSelection[2]).hasAValueOf("SPCE_RB_0");
}

TEST(testSingleRNEMD, singleFluxTypeCorrectInferredParameters)
{
    RNEMDInferredParametersPtr rnemdInferred { rnemdFile->getRNEMDInferredParameters() };

    assertThat(rnemdFile, rnemdInferred->numberOfRegions).hasAValueOf(2);
    assertThat(rnemdFile, rnemdInferred->slabWidth.getMagnitude()).hasAValueNear(39.1876);
    assertThat(rnemdFile, rnemdInferred->dataFieldLabelIndex).hasAValueOf(38);
    assertThat(rnemdFile, rnemdInferred->boxSize.getMagnitude()).hasAValueNear(78.37511346);
    assertThat(rnemdFile, rnemdInferred->hasSelectionB).isFalse();
}

TEST(testSingleRNEMD, singleFluxTypeCorrectReportParameters)
{
    RNEMDReportParametersPtr rnemdReport { rnemdFile->getRNEMDReportParameters() };

    assertThat(rnemdFile, rnemdReport->runningTime.getMagnitude()).hasAValueNear(10000002.0);


    // Target Fluxes
    assertThat(rnemdFile, rnemdReport->kineticFlux.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->momentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->angularMomentumFlux[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumFlux[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumFlux[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->currentDensity.getMagnitude()).hasAValueNear(6.241573e-09);


    // Target One-Time Exchanges
    assertThat(rnemdFile, rnemdReport->kineticTarget.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->momentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumTarget[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->angularMomentumTarget[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumTarget[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumTarget[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Exchange Totals
    assertThat(rnemdFile, rnemdReport->kineticExchange.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->momentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->momentumExchange[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->angularMomentumExchange[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumExchange[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->angularMomentumExchange[2].getMagnitude()).hasAValueNear(0.0);


    // Actual Fluxes
    assertThat(rnemdFile, rnemdReport->Jz.getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->JzP[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->JzP[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->JzP[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->JzL[0].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->JzL[1].getMagnitude()).hasAValueNear(0.0);
    assertThat(rnemdFile, rnemdReport->JzL[2].getMagnitude()).hasAValueNear(0.0);

    assertThat(rnemdFile, rnemdReport->Jc_total.getMagnitude()).hasAValueNear(3.2316331e-09);
    assertThat(rnemdFile, rnemdReport->Jc_cation.getMagnitude()).hasAValueNear(1.9603903e-09);
    assertThat(rnemdFile, rnemdReport->Jc_anion.getMagnitude()).hasAValueNear(1.2712428e-09);


    // Exchange Statistics
    assertThat(rnemdFile, rnemdReport->trialCount).hasAValueOf(5000000);
    assertThat(rnemdFile, rnemdReport->failTrialCount).hasAValueOf(2411203);
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
        std::vector<ElectricPotential> Phi { individualRegionData->electricPotential };

        std::ofstream outputFile;
        outputFile.open("Single" + std::to_string(region) + ".txt");

        for (size_t j {}; j < z.size(); ++j)
            outputFile << z[j] << " " << temp[j] << " "
                       << concAnion[j] << " " << concCation[j] << " "
                       << Ez[j].convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol",
                            "eV_part")) << " "
                       << Phi[j].convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol",
                            "eV_part")) << std::endl;
        outputFile.close();

        sizeOfRNEMDAxis += z.size();
    }

    ASSERT_EQ(rnemdData->rnemdAxis.size(), sizeOfRNEMDAxis);
}
