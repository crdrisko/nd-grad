// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testRegionSplitting.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/22/2020-20:37:57
// Description: Provides 100% unit test coverage over all region splitting functions

#include <array>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <gtest/gtest.h>

#include "../../RNEMDFileParsing/include/rnemdRegion.hpp"

using namespace OpenMD::RNEMD;
using namespace PhysicalQuantities;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testRegionSplitting, currentFluxTypeCorrectSplitting)
{
    RNEMDFilePtr rnemdFile { std::make_shared<RNEMDFile>("../../samples/double.rnemd") };

    unsigned int sizeOfRNEMDAxis {};
    RNEMDDataPtr rnemdData { rnemdFile->getAllDataFromFile() };

    RNEMDRegionPtr rnemdRegionData { std::make_shared<RNEMDRegion>(rnemdFile) };
    std::vector<RNEMDDataPtr> individualRegionData { rnemdRegionData->getRegionSpecificData() };

    // Test Correct Region Specific Data
    for (int region {1}; region <= rnemdFile->getRNEMDParameters()->inferred->numberOfRegions; ++region)
    {
        std::vector<Length> z { individualRegionData[region - 1]->rnemdAxis };
        std::vector<Temperature> temp { individualRegionData[region - 1]->temperature };
        std::vector<Concentration> concAnion { individualRegionData[region - 1]->activity[0] };
        std::vector<Concentration> concCation { individualRegionData[region - 1]->activity[1] };
        std::vector<ElectricField> Ez { individualRegionData[region - 1]->electricField[2] };
        std::vector<ElectricPotential> Phi { individualRegionData[region - 1]->electricPotential };

        std::ofstream outputFile;
        outputFile.open("Current" + std::to_string(region) + ".txt");

        for (size_t j {}; j < z.size(); ++j)
            outputFile << z[j] << " " << temp[j] << " "
                       << concAnion[j] << " " << concCation[j] << " "
                       << Ez[j].convertQuantity("kcal_mol", "eV_part") << " "
                       << Phi[j].convertQuantity("kcal_mol", "eV_part") << std::endl;

        outputFile.close();

        sizeOfRNEMDAxis += z.size();
    }

    ASSERT_EQ(rnemdData->rnemdAxis.size(), sizeOfRNEMDAxis);
}

TEST(testRegionSplitting, KE_FluxTypeCorrectSplitting)
{
    RNEMDFilePtr rnemdFile { std::make_shared<RNEMDFile>("../../samples/thermal.rnemd") };

    unsigned int sizeOfRNEMDAxis {};
    RNEMDDataPtr rnemdData { rnemdFile->getAllDataFromFile() };

    RNEMDRegionPtr rnemdRegionData { std::make_shared<RNEMDRegion>(rnemdFile) };
    std::vector<RNEMDDataPtr> individualRegionData { rnemdRegionData->getRegionSpecificData() };

    // Test Correct Region Specific Data
    for (int region {1}; region <= rnemdFile->getRNEMDParameters()->inferred->numberOfRegions; ++region)
    {
        std::vector<Length> z { individualRegionData[region - 1]->rnemdAxis };
        std::vector<Temperature> temp { individualRegionData[region - 1]->temperature };

        std::ofstream outputFile;
        outputFile.open("Thermal" + std::to_string(region) + ".txt");

        for (size_t j {}; j < z.size(); ++j)
            outputFile << z[j] << " " << temp[j] << std::endl;

        outputFile.close();

        sizeOfRNEMDAxis += z.size();
    }

    ASSERT_EQ(rnemdData->rnemdAxis.size(), sizeOfRNEMDAxis);
}

TEST(testRegionSplitting, Px_FluxTypeCorrectSplitting)
{
    RNEMDFilePtr rnemdFile { std::make_shared<RNEMDFile>("../../samples/momentum.rnemd") };

    unsigned int sizeOfRNEMDAxis {};
    RNEMDDataPtr rnemdData { rnemdFile->getAllDataFromFile() };

    RNEMDRegionPtr rnemdRegionData { std::make_shared<RNEMDRegion>(rnemdFile) };
    std::vector<RNEMDDataPtr> individualRegionData { rnemdRegionData->getRegionSpecificData() };

    // Test Correct Region Specific Data
    for (int region {1}; region <= rnemdFile->getRNEMDParameters()->inferred->numberOfRegions; ++region)
    {
        std::vector<Length> z { individualRegionData[region - 1]->rnemdAxis };
        std::vector<Temperature> temp { individualRegionData[region - 1]->temperature };
        std::array<std::vector<Velocity>, 3> velocity { individualRegionData[region - 1]->velocity };
        std::vector<MassDensity> density { individualRegionData[region - 1]->density };

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

TEST(testRegionSplitting, singleFluxTypeCorrectRegionSplitting)
{
    RNEMDFilePtr rnemdFile { std::make_shared<RNEMDFile>("../../samples/single.rnemd") };

    unsigned int sizeOfRNEMDAxis {};
    RNEMDDataPtr rnemdData { rnemdFile->getAllDataFromFile() };

    RNEMDRegionPtr rnemdRegionData { std::make_shared<RNEMDRegion>(rnemdFile) };
    std::vector<RNEMDDataPtr> individualRegionData { rnemdRegionData->getRegionSpecificData() };

    // Test Correct Region Specific Data
    for (int region {1}; region <= rnemdFile->getRNEMDParameters()->inferred->numberOfRegions; ++region)
    {
        std::vector<Length> z { individualRegionData[region - 1]->rnemdAxis };
        std::vector<Temperature> temp { individualRegionData[region - 1]->temperature };
        std::vector<Concentration> concAnion { individualRegionData[region - 1]->activity[0] };
        std::vector<Concentration> concCation { individualRegionData[region - 1]->activity[1] };
        std::vector<ElectricField> Ez { individualRegionData[region - 1]->electricField[2] };
        std::vector<ElectricPotential> Phi { individualRegionData[region - 1]->electricPotential };

        std::ofstream outputFile;
        outputFile.open("Single" + std::to_string(region) + ".txt");

        for (size_t j {}; j < z.size(); ++j)
            outputFile << z[j] << " " << temp[j] << " "
                       << concAnion[j] << " " << concCation[j] << " "
                       << Ez[j].convertQuantity("kcal_mol", "eV_part") << " "
                       << Phi[j].convertQuantity("kcal_mol", "eV_part") << std::endl;

        outputFile.close();

        sizeOfRNEMDAxis += z.size();
    }

    ASSERT_EQ(rnemdData->rnemdAxis.size(), sizeOfRNEMDAxis);
}
