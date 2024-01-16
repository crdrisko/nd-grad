// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testShiftXYZ.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/24/2020-07:42:39
// Description: Provides 100% unit test coverage over all functions for the ShiftXYZ program

#include <fstream>
#include <memory>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <gtest/gtest.h>

#include "../../ShiftXYZ/include/xyzFile.hpp"

using namespace OpenMD::RNEMD;
using namespace PhysicalQuantities::Literals;

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(testShiftXYZ, testProperXYZParameters)
{
    XYZFilePtr xyzFile { std::make_shared<XYZFile>("../../samples/single.xyz") };
    XYZParametersPtr xyzParameters { xyzFile->getXYZParameters() };

    ASSERT_EQ(4680, xyzParameters->numberOfAtoms);
    ASSERT_DOUBLE_EQ(10'000'002.0, xyzParameters->runTime.getMagnitude());

    ASSERT_DOUBLE_EQ(24.49222299, xyzParameters->Hmat[0][0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0,         xyzParameters->Hmat[0][1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0,         xyzParameters->Hmat[0][2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0,         xyzParameters->Hmat[1][0].getMagnitude());
    ASSERT_DOUBLE_EQ(24.49222299, xyzParameters->Hmat[1][1].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0,         xyzParameters->Hmat[1][2].getMagnitude());

    ASSERT_DOUBLE_EQ(0.0,         xyzParameters->Hmat[2][0].getMagnitude());
    ASSERT_DOUBLE_EQ(0.0,         xyzParameters->Hmat[2][1].getMagnitude());
    ASSERT_DOUBLE_EQ(78.37511358, xyzParameters->Hmat[2][2].getMagnitude());

    ASSERT_EQ(static_cast<unsigned int>(4680), xyzParameters->atomLabels.size());
    ASSERT_EQ(static_cast<unsigned int>(4680), xyzParameters->coordinates[0].size());
    ASSERT_EQ(static_cast<unsigned int>(4680), xyzParameters->coordinates[1].size());
    ASSERT_EQ(static_cast<unsigned int>(4680), xyzParameters->coordinates[2].size());
}

TEST(testShiftXYZ, testProperOutputFilePrinting)
{
    XYZFilePtr xyzFile { std::make_shared<XYZFile>("../../samples/single.xyz") };

    xyzFile->shiftXYZPositions( 19.5938_Ang );
    xyzFile->printOutputToFile("shifted_single.txt");

    std::ifstream outputFile {"shifted_single.txt"};

    ASSERT_TRUE(outputFile);
}

TEST(testShiftXYZ, testOnlySpecifiedChangesAreMade)
{
    XYZFilePtr xyzFile { std::make_shared<XYZFile>("../../samples/single.xyz") };
    XYZParametersPtr xyzParameters { xyzFile->getXYZParameters() };

    std::vector<PhysicalQuantities::Length> initialZCoordinates { xyzParameters->coordinates[2] };

    xyzFile->shiftXYZPositions( 19.5938_Ang );

    for (size_t i {}; i < initialZCoordinates.size(); ++i)
    {
        if ( initialZCoordinates[i] > 19.5938_Ang )
            ASSERT_DOUBLE_EQ( xyzParameters->coordinates[2][i].getMagnitude(),
                (initialZCoordinates[i] - xyzParameters->Hmat[2][2]).getMagnitude() );
        else
            ASSERT_DOUBLE_EQ( xyzParameters->coordinates[2][i].getMagnitude(),
                initialZCoordinates[i].getMagnitude() );
    }
}
