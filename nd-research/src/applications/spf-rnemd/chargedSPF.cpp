// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: chargedSPF.cpp
// Author: crdrisko
// Date: 09/19/2024-09:09:58
// Description:

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <set>
#include <vector>

#include <common-utils/math.hpp>

#include "rnemdFile.hpp"

using namespace CppUnits;
using namespace Literals;
using namespace ND_Research;

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path> \n";
        return EXIT_FAILURE;
    }

    const auto ConversionFactor = (4184.0 * 6.2415e18 / Constants::avogadrosNumber);

    RNEMDFile rnemdFile {argv[1]};

    RNEMDData data         = rnemdFile.getRNEMDData();
    RNEMDData errors       = rnemdFile.getRNEMDErrors();
    RNEMDParameters params = rnemdFile.getRNEMDParameters();

    ElectricField sum {};
    int count {};

    for (auto iter {data.electricField.begin() + params.inferred.boundaryB_end};
         iter != data.electricField.begin() + params.inferred.boundaryA_start;
         ++iter)
    {
        sum += Math::abs(iter->at(2));
        count++;
    }

    for (auto iter {data.electricField.begin() + params.inferred.boundaryA_end};
         iter != data.electricField.begin() + params.inferred.boundaryB_start;
         ++iter)
    {
        sum += Math::abs(iter->at(2));
        count++;
    }

    std::cout << (sum / count) * ConversionFactor << " V / Ang\n";
}
