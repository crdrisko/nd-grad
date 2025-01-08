// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
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

    std::string dirName {argv[1]};
    fs::path outputFileName {dirName};
    std::string fileName = outputFileName.string() + "/../" + outputFileName.stem().string();

    std::ofstream outputFile;
    outputFile.open(fileName + ".csv");

    outputFile << std::setw(13) << "# Time  Jc_applied," << std::setw(19) << "Jc_actual," << std::setw(13) << "dCation_dz,"
               << std::setw(13) << "dAnion_dz," << std::setw(13) << "EField\n";

    const auto ConversionFactor = (4184.0 * 6.2415e18 / Constants::avogadrosNumber);

    // Sort the filenames
    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".rnemd")
            paths.insert(dirEntry.path().string());

    for (const auto& path : paths)
    {
        RNEMDFile rnemdFile {path};

        RNEMDData data         = rnemdFile.getRNEMDData();
        RNEMDData errors       = rnemdFile.getRNEMDErrors();
        RNEMDParameters params = rnemdFile.getRNEMDParameters();

        ElectricField sum {};
        int count {};

        for (auto iter {data.electricField.begin() + params.inferred.boundaryB_end};
             iter != data.electricField.begin() + params.inferred.boundaryA_start;
             ++iter)
        {
            sum += iter->at(2);
            count++;
        }

        for (auto iter {data.electricField.begin() + params.inferred.boundaryA_end};
             iter != data.electricField.begin() + params.inferred.boundaryB_start;
             ++iter)
        {
            sum -= iter->at(2);
            count++;
        }

        for (std::size_t i {}; i < data.activity[0].size(); ++i)
        {
            data.activity[0][i] = 1.0_M * Math::log(data.activity[0][i]);
            data.activity[1][i] = 1.0_M * Math::log(data.activity[1][i]);
        }

        auto dCation1_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryB_end,
            data.rnemdAxis.begin() + params.inferred.boundaryA_start,
            data.activity[0].begin() + params.inferred.boundaryB_end,
            data.activity[0].begin() + params.inferred.boundaryA_start);

        auto dAnion1_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryB_end,
            data.rnemdAxis.begin() + params.inferred.boundaryA_start,
            data.activity[1].begin() + params.inferred.boundaryB_end,
            data.activity[1].begin() + params.inferred.boundaryA_start);

        auto dCation2_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryA_end,
            data.rnemdAxis.begin() + params.inferred.boundaryB_start,
            data.activity[0].begin() + params.inferred.boundaryA_end,
            data.activity[0].begin() + params.inferred.boundaryB_start);

        auto dAnion2_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryA_end,
            data.rnemdAxis.begin() + params.inferred.boundaryB_start,
            data.activity[1].begin() + params.inferred.boundaryA_end,
            data.activity[1].begin() + params.inferred.boundaryB_start);

        ConcentrationGradient dCation_dz = (dCation1_dz.slope - dCation2_dz.slope) / 2;
        ConcentrationGradient dAnion_dz  = (dAnion1_dz.slope - dAnion2_dz.slope) / 2;

        std::size_t numberStart {path.find("stitch") + 7};
        std::size_t numberEnd {path.find(".rnemd")};

        outputFile << std::setw(4) << (std::stoi(path.substr(numberStart, numberEnd - numberStart))) << ',';

        outputFile << std::setw(12) << params.report.currentDensity << ',' << std::setw(18) << params.report.Jc << ','
                   << std::setw(12) << dCation_dz << ',' << std::setw(12) << dAnion_dz << ',' << std::setw(12)
                   << (sum / count) * ConversionFactor << '\n';
    }
}
