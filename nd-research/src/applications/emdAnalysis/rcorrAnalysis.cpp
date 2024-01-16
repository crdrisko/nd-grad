// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: rcorrAnalysis.cpp
// Author: crdrisko
// Date: 09/18/2023-14:59:40
// Description:

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <common-utils/math.hpp>

#include "emdFile.hpp"

using namespace ND_Research;

namespace fs = std::filesystem;

struct Results
{
    std::vector<double> x;
    std::vector<double> rmsd;
};

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

    std::set<std::string> paths_11, paths_22;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
    {
        if (dirEntry.path().extension().string() == ".rcorr")
        {
            if (DryChem::foundSubstr("blue", dirEntry.path().string())
                || DryChem::foundSubstr("Ar", dirEntry.path().string()))
            {
                paths_11.insert(dirEntry.path().string());
            }
            else if (DryChem::foundSubstr("red", dirEntry.path().string())
                     || DryChem::foundSubstr("Kr", dirEntry.path().string()))
            {
                paths_22.insert(dirEntry.path().string());
            }
        }
    }

    std::vector<Results> input_11 = parseInputFiles<Results>(paths_11);

    Results output_11 = calculateAverages(input_11);
    Results errors_11 = calculateStdDev(output_11, input_11);

    std::vector<Results> input_22 = parseInputFiles<Results>(paths_22);

    Results output_22 = calculateAverages(input_22);
    Results errors_22 = calculateStdDev(output_22, input_22);

    std::ofstream outputFileStream;
    outputFileStream.open(fileName + ".txt");

    outputFileStream.precision(8);

    if (output_11.x.size() == output_22.x.size())
    {
        // Skip first point so (1 / t) doesn't diverge
        for (std::size_t bin {1}; bin < output_11.x.size(); ++bin)
        {
            outputFileStream << output_11.x[bin] << '\t' << output_11.rmsd[bin] << '\t' << output_22.rmsd[bin] << '\t'
                             << errors_11.rmsd[bin] << '\t' << errors_22.rmsd[bin] << '\n';
        }
    }

    auto D_11 = DryChem::linearLeastSquaresFitting(output_11.x.begin(),
        output_11.x.end(),
        output_11.rmsd.begin(),
        output_11.rmsd.end());

    auto D_22 = DryChem::linearLeastSquaresFitting(output_22.x.begin(),
        output_22.x.end(),
        output_22.rmsd.begin(),
        output_22.rmsd.end());

    std::cout << "11 = Ar_blue or Ar; 22 = Ar_red or Kr\n";
    std::cout << "D_11: " << (D_11.slope / 6.0 * 10000.0) << " Ang^2 / ps\nD_22:  " << (D_22.slope / 6.0 * 1000.0)
              << " Ang^2 / ps\n";
}
