// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: fzConstraintAnalysis.cpp
// Author: crdrisko
// Date: 04/28/2024-10:12:45
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

    // std::cout << fileName << '\n';

    // Sort the filenames
    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".fz")
            paths.insert(dirEntry.path().string());

    for (const auto& path : paths)
    {
        FZFile fzFile {path};

        std::map<std::size_t, std::size_t> counts {};
        std::map<std::size_t, Force> sumForces {};

        for (const auto& param : fzFile.getFZParams())
        {
            for (const auto& [id, zConstraints] : param.moleculeData)
            {
                sumForces[id] += zConstraints.force;
                counts[id]++;
            }
        }

        // std::cout << "Constraint ID | Counts | Forces (kcal/mol/Ang)\n";

        Force deltaF {};

        for (const auto& [id, count] : counts)
        {
            // std::cout << std::setw(7) << id << std::setw(15) << count << std::setw(17) << sumForces[id] / count << '\n';
            deltaF += Math::abs(sumForces[id] / count);
        }

        try
        {
            outputFile << (2 * std::stoi(path.substr(15, 2)) - 1) << ", " << deltaF << '\n';
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
