// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testAllFluxTypes.cpp - Version 1.0.0
// Author: cdrisko
// Date: 03/10/2020-07:29:59
// Description: Run all the flux type tests with googletest

#include <gtest/gtest.h>

#include "FluxType_Current/testCurrent_RNEMD.hpp"
#include "FluxType_KE/testKE_RNEMD.hpp"
#include "FluxType_Px/testPx_RNEMD.hpp"
#include "FluxType_Single/testSingle_RNEMD.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
