// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: spfFitting.cpp
// Author: crdrisko
// Date: 04/14/2023-10:35:52
// Description:

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <set>
#include <vector>

#include <common-utils/math.hpp>

#include "rnemdFile.hpp"

using namespace CppUnits;
using namespace ND_Research;

namespace fs = std::filesystem;

void printDataOutputFile(std::ofstream& outputFile,
    ParticleFlux Jp_applied,
    ParticleFlux Jp_actual,
    double Failed_ratio,
    ConcentrationGradient dAr_dz,
    ConcentrationGradient dKr_dz,
    double ci_Ar95,
    double ci_Kr95);

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

    outputFile << std::setw(13) << "# Jp_applied," << std::setw(19) << "Jp_actual," << std::setw(19) << "Failed_percent,"
               << std::setw(13) << "dAr_dz," << std::setw(13) << "dKr_dz," << std::setw(19) << "95% CI Ar," << std::setw(19)
               << "95% CI Kr\n";

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

        double fails {static_cast<double>(params.report.failTrialCount) / static_cast<double>(params.report.trialCount)};

        int boundaryA_start = rnemdFile.determineRegionBounds(params.block.selectionA[0]);
        int boundaryA_end   = rnemdFile.determineRegionBounds(params.block.selectionA[1]);
        int boundaryB_start = rnemdFile.determineRegionBounds(params.block.selectionB[0]);
        int boundaryB_end   = rnemdFile.determineRegionBounds(params.block.selectionB[1]);

        auto dAr1_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + boundaryB_end,
            data.rnemdAxis.begin() + boundaryA_start,
            data.activity[0].begin() + boundaryB_end,
            data.activity[0].begin() + boundaryA_start);

        auto dKr1_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + boundaryB_end,
            data.rnemdAxis.begin() + boundaryA_start,
            data.activity[1].begin() + boundaryB_end,
            data.activity[1].begin() + boundaryA_start);

        auto dAr2_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + boundaryA_end,
            data.rnemdAxis.begin() + boundaryB_start,
            data.activity[0].begin() + boundaryA_end,
            data.activity[0].begin() + boundaryB_start);

        auto dKr2_dz = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + boundaryA_end,
            data.rnemdAxis.begin() + boundaryB_start,
            data.activity[1].begin() + boundaryA_end,
            data.activity[1].begin() + boundaryB_start);

        ConcentrationGradient dAr_dz = Math::abs(dAr1_dz.slope - dAr2_dz.slope) / 2;
        ConcentrationGradient dKr_dz = Math::abs(dKr1_dz.slope - dKr2_dz.slope) / 2;

        double ci_Ar95 = 1.96 * (0.5 * Math::sqrt(dAr1_dz.variance + dAr2_dz.variance).getMagnitude()) / std::sqrt(2);
        double ci_Kr95 = 1.96 * (0.5 * Math::sqrt(dKr1_dz.variance + dKr2_dz.variance).getMagnitude()) / std::sqrt(2);

        outputFile << std::setw(4) << (2 * std::stoi(path.substr(88, 2)) - 1) << ',';

        printDataOutputFile(outputFile,
            params.report.particleFlux,
            params.report.Jp,
            fails,
            dAr_dz,
            dKr_dz,
            ci_Ar95,
            ci_Kr95);
    }
}

void printDataOutputFile(std::ofstream& outputFile,
    ParticleFlux Jp_applied,
    ParticleFlux Jp_actual,
    double Failed_ratio,
    ConcentrationGradient dAr_dz,
    ConcentrationGradient dKr_dz,
    double ci_Ar95,
    double ci_Kr95)
{
    outputFile << std::setw(12) << Jp_applied << ',';
    outputFile << std::setw(18) << Jp_actual << ',';
    outputFile << std::setw(18) << Failed_ratio << ',';
    outputFile << std::setw(12) << dAr_dz << ',';
    outputFile << std::setw(12) << dKr_dz << ',';
    outputFile << std::setw(18) << ci_Ar95 << ',';
    outputFile << std::setw(18) << ci_Kr95;

    outputFile << std::endl;
}