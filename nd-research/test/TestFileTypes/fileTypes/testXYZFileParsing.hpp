// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testXYZFileParsing.hpp - Version 1.0.0
// Author: crdrisko
// Date: 04/14/2020-16:28:35
// Description: Provides ~100% unit test coverage over the XYZFile class and functions

#ifndef ND_RESEARCH_TESTXYZFILEPARSING_HPP
#define ND_RESEARCH_TESTXYZFILEPARSING_HPP

#include <gtest/gtest.h>

#include "../../testAssertions.hpp"
#include "../../../src/fileTypes/xyzFiles/xyzFile.hpp"

namespace ND_Research
{
    GTEST_TEST(testXYZFileParsing, correctFrameParameters)
    {
        XYZFile xyzFile {"../../samples/single.xyz"};
        XYZParametersPtr xyzParameters { xyzFile.getXYZParameters() };

        assertThat(xyzParameters->frame[0].numberOfAtoms).hasAValueOf(4680);
        assertThat(xyzParameters->frame[0].runTime.getMagnitude()).hasAValueNear(10'000'002.0);

        assertThat(xyzParameters->frame[0].Hmat.x().x().getMagnitude()).hasAValueNear(24.49222299);
        assertThat(xyzParameters->frame[0].Hmat.x().y().getMagnitude()).hasAValueNear(0.0);
        assertThat(xyzParameters->frame[0].Hmat.x().z().getMagnitude()).hasAValueNear(0.0);

        assertThat(xyzParameters->frame[0].Hmat.y().x().getMagnitude()).hasAValueNear(0.0);
        assertThat(xyzParameters->frame[0].Hmat.y().y().getMagnitude()).hasAValueNear(24.49222299);
        assertThat(xyzParameters->frame[0].Hmat.y().z().getMagnitude()).hasAValueNear(0.0);

        assertThat(xyzParameters->frame[0].Hmat.z().x().getMagnitude()).hasAValueNear(0.0);
        assertThat(xyzParameters->frame[0].Hmat.z().y().getMagnitude()).hasAValueNear(0.0);
        assertThat(xyzParameters->frame[0].Hmat.z().z().getMagnitude()).hasAValueNear(78.37511358);
    }

    GTEST_TEST(testXYZFileParsing, correctInferredParameters)
    {
        XYZFile xyzFile {"../../samples/single.xyz"};
        XYZParametersPtr xyzParameters { xyzFile.getXYZParameters() };

        assertThat(xyzParameters->inferred.numberOfFrames).hasAValueOf(1);
        assertThat(xyzParameters->inferred.timeStep.getMagnitude()).hasAValueNear(0.0);
    }

    // GTEST_TEST(testXYZFileParsing, incorrectInternalFileDataThrowsExceptions)
    // {
    //     ASSERT_DEATH(
    //     {
    //         XYZFile xyzFile {"testFileTypeParsing.cpp"};
    //     }, "ND-Research Fatal Error:\n\tCould not convert a string value from the file into parameter type using: stoul\n");
    // }

    GTEST_TEST(testXYZFileParsing, componentsOfTheXYZFileNameAreCorrect)
    {
        XYZFile xyzFile {"../../samples/single.xyz"};

        assertThat(xyzFile.getFileName().getFileExtension()).hasAValueOf("xyz");
        assertThat(xyzFile.getFileName().getBaseFileName()).hasAValueOf("single.xyz");
        assertThat(xyzFile.getFileName().getRelativePathToFile()).hasAValueOf("../../samples");
        assertThat(xyzFile.getFileName().getFullFileName()).hasAValueOf("../../samples/single.xyz");
    }
}

#endif
