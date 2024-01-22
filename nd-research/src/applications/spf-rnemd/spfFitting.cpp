// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
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
using namespace Literals;
using namespace ND_Research;

namespace fs = std::filesystem;

using DiffusionConstant = PhysicalQuantity<Dimensionality<2, 0, -1>>;

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

    // std::fstream testFile("/Users/crdrisko/Desktop/SPF/SPF-Results/ArgonRed/ArgonGrubbsTest.csv",
    //     std::ios::out | std::ios::app);

    // testFile << "# " << fs::current_path().string().substr(49, 22) + "/" + outputFileName.stem().string() << '\n';

    outputFile << std::setw(13) << "# Jp_applied," << std::setw(19) << "Jp_actual," << std::setw(13) << "dAr_dz,"
               << std::setw(13) << "dKr_dz," << std::setw(13) << "D_Ar," << std::setw(13) << "D_Kr\n";

    const auto ConversionFactor = (1000.0 * 1.0_mol / Constants::avogadrosNumber) / 1.0e-27;

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

        // double ci_Ar95 = 1.96 * (0.5 * Math::sqrt(dAr1_dz.variance + dAr2_dz.variance).getMagnitude()) / std::sqrt(2);
        // double ci_Kr95 = 1.96 * (0.5 * Math::sqrt(dKr1_dz.variance + dKr2_dz.variance).getMagnitude()) / std::sqrt(2);

        DiffusionConstant D_Ar = params.report.Jp / (Math::abs(dAr1_dz.slope - dAr2_dz.slope) / 2) * ConversionFactor;
        DiffusionConstant D_Kr = params.report.Jp / (Math::abs(dKr1_dz.slope - dKr2_dz.slope) / 2) * ConversionFactor;

        // outputFile << std::setw(4) << (2 * std::stoi(path.substr(88, 2)) - 1) << ',';
        // outputFile << std::setw(4) << (2 * std::stoi(path.substr(15, 2)) - 1) << ',';

        // testFile << std::setw(18) << params.report.Jp << ',' << std::setw(12) << dAr1_dz.slope << ',' << std::setw(12)
        //          << dAr2_dz.slope << '\n';

        outputFile << std::setw(12) << params.report.particleFlux << ',' << std::setw(18) << params.report.Jp << ','
                   << std::setw(12) << dAr_dz << ',' << std::setw(12) << dKr_dz << ',' << std::setw(12) << D_Ar << ','
                   << std::setw(12) << D_Kr << '\n';
    }
}
