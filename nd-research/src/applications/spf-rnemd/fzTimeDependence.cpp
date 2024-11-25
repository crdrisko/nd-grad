// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: fzTimeDependence.cpp
// Author: crdrisko
// Date: 11/25/2024-06:03:32
// Description:

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <set>
#include <vector>

#include <common-utils/math.hpp>

#include "fzFile.hpp"

using namespace CppUnits;
using namespace Literals;
using namespace ND_Research;

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path>\n";
        return EXIT_FAILURE;
    }

    std::string dirName {argv[1]};
    fs::path outputFileName {dirName};
    std::string fileName = outputFileName.string() + "/../" + outputFileName.stem().string();

    std::ofstream outputFile;
    outputFile.open(fileName + ".txt");

    // Sort the filenames
    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".fz")
            paths.insert(dirEntry.path().string());

    std::map<Time, Force> vals {};

    for (const auto& path : paths)
    {
        FZFile fzFile {path};

        Force sumForces {};

        for (const auto& param : fzFile.getFZParams())
        {
            for (const auto& [id, zConstraints] : param.moleculeData)
            {
                sumForces += Math::abs(zConstraints.force);
            }

            vals[param.time] += sumForces / param.numberOfZConstraints; 
        }
    }

    for (const auto& [time, forces] : vals)
        outputFile << time << ", " << (forces / paths.size()) << '\n';
}
