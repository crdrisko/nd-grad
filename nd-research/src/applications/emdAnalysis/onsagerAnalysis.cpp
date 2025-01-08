// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: onsagerAnalysis.cpp
// Author: crdrisko
// Date: 09/17/2023-08:05:17
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
    std::vector<double> L11;
    std::vector<double> L12;
    std::vector<double> L22;
};

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <path> <prefactor>\n";
        return EXIT_FAILURE;
    }

    std::string dirName {argv[1]};
    fs::path outputFileName {dirName};
    std::string fileName = outputFileName.string() + "/../" + outputFileName.stem().string();

    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".onsager")
            paths.insert(dirEntry.path().string());

    std::vector<Results> input = parseInputFiles<Results>(paths);

    Results output = calculateAverages(input);
    Results errors = calculateStdDev(output, input);

    std::ofstream outputFileStream;
    outputFileStream.open(fileName + ".txt");

    outputFileStream.precision(8);

    // Skip first point so (1 / t) doesn't diverge
    for (std::size_t bin {1}; bin < output.x.size(); ++bin)
    {
        outputFileStream << output.x[bin] << '\t' << output.L11[bin] << '\t' << output.L12[bin] << '\t' << output.L22[bin]
                         << '\t' << errors.L11[bin] << '\t' << errors.L12[bin] << '\t' << errors.L22[bin] << '\n';
    }

    auto fit_L11
        = DryChem::linearLeastSquaresFitting(output.x.begin(), output.x.end(), output.L11.begin(), output.L11.end());
    auto fit_L12
        = DryChem::linearLeastSquaresFitting(output.x.begin(), output.x.end(), output.L12.begin(), output.L12.end());
    auto fit_L22
        = DryChem::linearLeastSquaresFitting(output.x.begin(), output.x.end(), output.L22.begin(), output.L22.end());

    double prefactor = std::stod(argv[2]);

    std::cout << "D_12: "
              << ((prefactor * fit_L11.slope + (1.0 / prefactor) * fit_L22.slope - 2.0 * fit_L12.slope) / (6.0 * 2744.0)
                     * 1000.0)
              << " Ang^2 / ps\n";
}