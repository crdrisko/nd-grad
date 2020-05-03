// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testAllFluxTypes.cpp - Version 1.0.0
// Author: cdrisko
// Date: 03/10/2020-07:29:59
// Description: Provides ~100% unit test coverage over all remaining fluxTypes in the samples directory

#include <gtest/gtest.h>

#include "fluxTypes/testKE_RNEMD.hpp"
#include "fluxTypes/testLx_RNEMD.hpp"
#include "fluxTypes/testNIVS_RNEMD.hpp"
#include "fluxTypes/testPx_RNEMD.hpp"
#include "fluxTypes/testSingle_RNEMD.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
