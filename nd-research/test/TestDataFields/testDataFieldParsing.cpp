// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testDataFieldParsing.cpp - Version 1.0.0
// Author: cdrisko
// Date: 05/14/2020-08:06:45
// Description: Provides ~100% unit test coverage over all data field parsing utilities in the repository

#include <gtest/gtest.h>

#include "dataFields/testDataFields.hpp"
#include "dataFields/testDataFieldParsing.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
