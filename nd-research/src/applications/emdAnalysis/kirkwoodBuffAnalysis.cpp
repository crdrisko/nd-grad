// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: kirkwoodBuffAnalysis.cpp
// Author: crdrisko
// Date: 06/23/2023-09:24:34
// Description:

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <common-utils/files.hpp>
#include <common-utils/strings.hpp>

#include "emdFile.hpp"

using namespace ND_Research;

namespace fs = std::filesystem;

struct Results
{
    std::vector<double> x;

    std::vector<double> g11;
    std::vector<double> g12;
    std::vector<double> g22;

    std::vector<double> cG11;
    std::vector<double> cG12;
    std::vector<double> cG22;

    std::vector<double> G11;
    std::vector<double> G12;
    std::vector<double> G22;
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
        if (dirEntry.path().extension().string() == ".kirkwood-buff")
            paths.insert(dirEntry.path().string());

    std::vector<Results> input = parseInputFiles<Results>(paths);

    Results output = calculateAverages(input);
    Results errors = calculateStdDev(output, input);

    double prefactor = std::stod(argv[2]);
    double Delta12   = output.G11.back() + output.G22.back() - 2 * output.G12.back();
    double Gamma12   = 1.0 - ((prefactor * Delta12) / (1.0 + (prefactor * Delta12)));

    double sigma_Delta12
        = std::sqrt((errors.G11.back() * errors.G11.back())
                    + (errors.G22.back() * errors.G22.back() + 4 * (errors.G12.back() * errors.G12.back())));

    double sigma_Gamma12 = sigma_Delta12 * (prefactor / ((1.0 + prefactor * Delta12) * (1.0 + prefactor * Delta12)));

    std::cout << Delta12 << " +/- " << sigma_Delta12 << "; 95% CI: [ "
              << (Delta12 - 1.96 * sigma_Delta12 / std::sqrt(input.size())) << ", "
              << (Delta12 + 1.96 * sigma_Delta12 / std::sqrt(input.size())) << " ]\n";

    std::cout << Gamma12 << " +/- " << sigma_Gamma12 << "; 95% CI: [ "
              << (Gamma12 - 1.96 * sigma_Gamma12 / std::sqrt(input.size())) << ", "
              << (Gamma12 + 1.96 * sigma_Gamma12 / std::sqrt(input.size())) << " ]\n";

    calculate95CIFromStdDev(errors, input.size());

    std::ofstream outputFileStream;
    outputFileStream.open(fileName + ".txt");

    outputFileStream.precision(8);

    for (std::size_t bin {}; bin < output.x.size(); ++bin)
    {
        outputFileStream << output.x[bin] << '\t' << output.G11[bin] << '\t' << output.G12[bin] << '\t' << output.G22[bin]
                         << '\t' << errors.G11[bin] << '\t' << errors.G12[bin] << '\t' << errors.G22[bin] << '\n';
    }
}
