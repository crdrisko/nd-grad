// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testFileTypeParsing.cpp - Version 1.0.0
// Author: crdrisko
// Date: 04/14/2020-16:28:20
// Description: Provides ~100% unit test coverage over all file parsing utilities in the repository

#include <gtest/gtest.h>

#include "fileTypes/testRNEMDFileParsing.hpp"
#include "fileTypes/testXYZFileParsing.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
