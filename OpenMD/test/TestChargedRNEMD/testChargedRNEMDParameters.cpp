// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: testChargedRNEMDParameters.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/23/2020-16:10:23
// Description: Provides 100% unit test coverage over all parameter parsing functions for Charged-RNEMD

#include <gtest/gtest.h>
#include "../../ChargedRNEMD/include/chargedRNEMDFile.hpp"

using namespace OpenMD::RNEMD::ChargedRNEMD;
using namespace Utilities_API;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testChargedRNEMDParameters, correctChargeParameters)
{
    std::vector<std::string> files { "../../samples/double.rnemd",
                                     "../../samples/single.rnemd",
                                     "../../samples/thermal.rnemd",
                                     "../../samples/momentum.rnemd" };

    for (const auto& file : files)
    {
        Files::FileNamePtr fileName { std::make_shared<Files::FileName>(file) };

        if ( (fileName->getBaseFileName() == "thermal.rnemd")
            || (fileName->getBaseFileName() == "momentum.rnemd") )
        {
            ASSERT_DEATH(
            {
                ChargedRNEMDFilePtr rnemdFile { std::make_shared<ChargedRNEMDFile>(file) };
            }, "The supplied flux type does not match one of the Charged-RNEMD flux types");
        }
        else
        {
            ChargedRNEMDFilePtr rnemdFile { std::make_shared<ChargedRNEMDFile>(file) };
            ChargedRNEMDParametersPtr rnemdParameters { rnemdFile->getChargedRNEMDParameters() };

            ASSERT_EQ("Na+", rnemdParameters->ionicSpecies[1]->getIonName());
            ASSERT_EQ("Cl-", rnemdParameters->ionicSpecies[0]->getIonName());

            ASSERT_EQ(1, rnemdParameters->ionicSpecies[1]->getIonIndex());
            ASSERT_EQ(0, rnemdParameters->ionicSpecies[0]->getIonIndex());

            ASSERT_EQ(1.0, rnemdParameters->ionicSpecies[1]->getIonCharge().getMagnitude());
            ASSERT_EQ(-1.0, rnemdParameters->ionicSpecies[0]->getIonCharge().getMagnitude());
        }
    }
}

TEST(testChargedRNEMDParameters, testIonicChargeFunction)
{
    std::vector<std::string> ionNames {"Na+", "Li+", "Ca+2", "Cl-"};

    for (const auto& ionName : ionNames)
    {
        IonicSpeciesPtr ion { std::make_shared<IonicSpecies>(ionName) };

        if ( (ionName == "Na+") || (ionName == "Li+") )
        {
            ASSERT_EQ(1.0, ion->getIonCharge().getMagnitude());
        }
        else if (ionName == "Ca+2")
        {
            ASSERT_EQ(2.0, ion->getIonCharge().getMagnitude());
        }
        else if (ionName == "Cl-")
        {
            ASSERT_EQ(-1.0, ion->getIonCharge().getMagnitude());
        }
    }
}
