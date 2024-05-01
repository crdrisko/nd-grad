// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: membranePermeability.cpp
// Author: crdrisko
// Date: 04/13/2024-14:54:25
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

    // std::fstream testFile("/Users/crdrisko/Desktop/SPF/SPF-Results/Krypton/KryptonGrubbsTest.csv",
    //     std::ios::out | std::ios::app);

    // testFile << "# " << fs::current_path().string().substr(48, 23) + "/" + outputFileName.stem().string() << '\n';

    outputFile << std::setw(13) << "# Jp_applied," << std::setw(19) << "Jp_actual," << std::setw(13) << "dAr_dz,"
               << std::setw(13) << "dKr_dz," << std::setw(13) << "D_Ar," << std::setw(13) << "D_Kr\n";

    // const auto ConversionFactor = (1000.0 * 1.0_mol / Constants::avogadrosNumber) / 1.0e-27;

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

        // std::vector<Length> rnemdAxisO_02B {data.rnemdAxis.begin(),
        //     data.rnemdAxis.begin() + params.inferred.boundaryB_end + 10};
        // std::vector<Length> rnemdAxisO_A {data.rnemdAxis.begin() + params.inferred.boundaryA_start - 8,
        //     data.rnemdAxis.begin() + params.inferred.boundaryA_end + 10};
        // std::vector<Length> rnemdAxisO_B20 {data.rnemdAxis.begin() + params.inferred.boundaryB_start - 8,
        //     data.rnemdAxis.end()};

        // std::vector<Concentration> activityO_02B {data.activity[0].begin(),
        //     data.activity[0].begin() + params.inferred.boundaryB_end + 10};
        // std::vector<Concentration> activityO_A {data.activity[0].begin() + params.inferred.boundaryA_start - 8,
        //     data.activity[0].begin() + params.inferred.boundaryA_end + 10};
        // std::vector<Concentration> activityO_B20 {data.activity[0].begin() + params.inferred.boundaryB_start - 8,
        //     data.activity[0].end()};

        std::vector<Concentration> activityO_02B {data.activity[0].begin(),
            data.activity[0].begin() + params.inferred.boundaryB_end};
        std::vector<Concentration> activityO_A {data.activity[0].begin() + params.inferred.boundaryA_start,
            data.activity[0].begin() + params.inferred.boundaryA_end};
        std::vector<Concentration> activityO_B20 {data.activity[0].begin() + params.inferred.boundaryB_start,
            data.activity[0].end()};

        Concentration avgConcO_02B {}, avgConcO_A {}, avgConcO_B20 {};

        if (activityO_02B.size() + activityO_B20.size() == activityO_A.size())
        {
            for (std::size_t bin {}; bin < activityO_02B.size(); ++bin)
            {
                avgConcO_02B += activityO_02B[bin];
            }

            for (std::size_t bin {}; bin < activityO_A.size(); ++bin)
            {
                avgConcO_A += activityO_A[bin];
            }

            for (std::size_t bin {}; bin < activityO_B20.size(); ++bin)
            {
                avgConcO_B20 += activityO_B20[bin];
            }
        }
        else
        {
            std::cout << activityO_02B.size() << ' ' << activityO_B20.size() << ' ' << activityO_A.size() << '\n';
             std::exit(EXIT_FAILURE);
        }

        outputFile << std::setw(4) << (2 * std::stoi(path.substr(15, 2)) - 1) << ',';

        outputFile << std::setw(12) << params.report.particleFlux << ',' << std::setw(18) << params.report.Jp << ','
                   << std::setw(12) << (((avgConcO_02B + avgConcO_B20) - avgConcO_A) / activityO_A.size()) << '\n';
    }
}
