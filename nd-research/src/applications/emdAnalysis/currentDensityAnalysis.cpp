// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: currentDensityAnalysis.cpp
// Author: crdrisko
// Date: 10/11/2024-06:26:31
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
    std::vector<double> Jc;
};

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <path> <field>\n";
        return EXIT_FAILURE;
    }

    std::string dirName {argv[1]};
    fs::path outputFileName {dirName};
    std::string fileName = outputFileName.string() + "/../" + outputFileName.stem().string();

    const auto ConversionFactor = (1e15 * 1e10 * 1.602e-19) * 10;

    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".Jc")
            paths.insert(dirEntry.path().string());

    std::vector<Results> input = parseInputFiles<Results>(paths);

    Results output = calculateAverages(input);
    Results errors = calculateStdDev(output, input);

    std::ofstream outputFileStream;
    outputFileStream.open(fileName + ".txt");

    outputFileStream.precision(8);

    double avgJc   = DryChem::calculateAverage(output.Jc.begin(), output.Jc.end());
    double sigmaJc = {};
    double eField = std::stod(argv[2]);

    for (std::size_t bin {}; bin < output.x.size(); ++bin)
    {
        sigmaJc += (errors.Jc[bin] * errors.Jc[bin]);
        outputFileStream << output.x[bin] << '\t' << output.Jc[bin] << '\t' << errors.Jc[bin] << '\n';
    }

    sigmaJc = std::sqrt(sigmaJc) / output.x.size();

    std::cout << "J_c   = " << avgJc << " +/- " << sigmaJc << " (e / Ang^s / fs)\n"
              << "sigma = " << (avgJc / eField * ConversionFactor) << " +/- " << (sigmaJc / eField  * ConversionFactor) << " (mS / cm)\n";
}
