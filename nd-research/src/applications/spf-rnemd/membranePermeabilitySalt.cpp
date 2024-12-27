// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: membranePermeabilitySalt.cpp
// Author: crdrisko
// Date: 12/13/2024-06:07:55
// Description:

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <set>
#include <vector>

#include <common-utils/math.hpp>
#include <common-utils/strings.hpp>
#include <dryphys/dryphys.hpp>

#include "rnemdFile.hpp"

using namespace DryPhys::Literals;
using namespace CppUnits::Literals;
using namespace CppUnits;
using namespace ND_Research;

namespace fs = std::filesystem;

std::set<std::string> sortFilesWithExtension(const std::string& dirName, const std::string& extension)
{
    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(dirName))
        if (dirEntry.path().extension().string() == extension)
            paths.insert(dirEntry.path().string());

    return paths;
}

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

    outputFile << std::setw(5) << "# Num," << std::setw(13) << "Jp_applied," << std::setw(19) << "Jp_actual,"
               << std::setw(13) << "Conc Na+," << std::setw(13) << "Conc Cl-," << std::setw(13) << "Conc O_SPCE,"
               << std::setw(13) << "Conc H_SPCE\n";

    // Sort the filenames
    std::set<std::string> paths = sortFilesWithExtension(dirName, ".rnemd");

    int pathCount {};

    for (const auto& path : paths)
    {
        RNEMDFile rnemdFile {path};

        RNEMDData data         = rnemdFile.getRNEMDData();
        RNEMDData errors       = rnemdFile.getRNEMDErrors();
        RNEMDParameters params = rnemdFile.getRNEMDParameters();

        std::string punctuation {")\t\n"};
        DryChem::Tokenizer tok {params.inferred.dataLabels, punctuation};
        std::vector<std::string> splitRow = tok.split();

        int index {};
        int start {params.inferred.names2index["Conc"]};
        int cation_index {}, anion_index {}, O_index {}, H_index {};

        for (const auto& elem : splitRow)
        {
            switch (DryPhys::djb2Hash(elem.c_str()))
            {
            case "Na+"_sID:
            case "Ca2+"_sID:
                cation_index = index - start;
                break;
            case "Cl-"_sID:
                anion_index = index - start;
                break;
            case "O_SPCE"_sID:
                O_index = index - start;
                break;
            case "H_SPCE"_sID:
                H_index = index - start;
                break;
            default:
                break;
            }
            index++;
        }

        int leftGraphene_left   = rnemdFile.determineRegionBounds(-18.75_Ang - 3.75_Ang);
        int leftGraphene_right  = rnemdFile.determineRegionBounds(-18.75_Ang + 3.75_Ang);
        int rightGraphene_left  = rnemdFile.determineRegionBounds(18.75_Ang - 3.75_Ang);
        int rightGraphene_right = rnemdFile.determineRegionBounds(18.75_Ang + 3.75_Ang);

        if (pathCount++ == 0)
            std::cout << " |-----Water-----|--NPG--|---------Water---------|--NPG--|-----Water-----|\n"
                      << " |---B---|--Ion--|--NPG--|--Ion--|---A---|--Ion--|--NPG--|--Ion--|---B---|\n"
                      << "000\t00" << params.inferred.boundaryB_end << "\t0" << leftGraphene_left << "\t0"
                      << leftGraphene_right << "\t0" << params.inferred.boundaryA_start << "\t0"
                      << params.inferred.boundaryA_end << "\t0" << rightGraphene_left << "\t0" << rightGraphene_right
                      << "\t0" << params.inferred.boundaryB_start << "\t074\n\n";

        // Cation
        Concentration avgConc_cation_b2lgl
            = DryChem::calculateAverage(data.activity[cation_index].begin() + params.inferred.boundaryB_end,
                data.activity[cation_index].begin() + leftGraphene_left);

        Concentration avgConc_cation_lgr2a
            = DryChem::calculateAverage(data.activity[cation_index].begin() + leftGraphene_right,
                data.activity[cation_index].begin() + params.inferred.boundaryA_start);

        Concentration avgConc_cation_a2rgl
            = DryChem::calculateAverage(data.activity[cation_index].begin() + params.inferred.boundaryA_end,
                data.activity[cation_index].begin() + rightGraphene_left);

        Concentration avgConc_cation_rgr2b
            = DryChem::calculateAverage(data.activity[cation_index].begin() + rightGraphene_right,
                data.activity[cation_index].begin() + params.inferred.boundaryB_start);

        // Anion
        Concentration avgConc_anion_b2lgl
            = DryChem::calculateAverage(data.activity[anion_index].begin() + params.inferred.boundaryB_end,
                data.activity[anion_index].begin() + leftGraphene_left);

        Concentration avgConc_anion_lgr2a
            = DryChem::calculateAverage(data.activity[anion_index].begin() + leftGraphene_right,
                data.activity[anion_index].begin() + params.inferred.boundaryA_start);

        Concentration avgConc_anion_a2rgl
            = DryChem::calculateAverage(data.activity[anion_index].begin() + params.inferred.boundaryA_end,
                data.activity[anion_index].begin() + rightGraphene_left);

        Concentration avgConc_anion_rgr2b
            = DryChem::calculateAverage(data.activity[anion_index].begin() + rightGraphene_right,
                data.activity[anion_index].begin() + params.inferred.boundaryB_start);

        // Oxygen
        Concentration avgConc_O_s2lgl
            = DryChem::calculateAverage(data.activity[O_index].begin(), data.activity[O_index].begin() + leftGraphene_left);

        Concentration avgConc_O_lgr2rgl = DryChem::calculateAverage(data.activity[O_index].begin() + leftGraphene_right,
            data.activity[O_index].begin() + rightGraphene_left);

        Concentration avgConc_O_rgr2e
            = DryChem::calculateAverage(data.activity[O_index].begin() + rightGraphene_right, data.activity[O_index].end());

        // Hydrogen
        Concentration avgConc_H_s2lgl
            = DryChem::calculateAverage(data.activity[H_index].begin(), data.activity[H_index].begin() + leftGraphene_left);

        Concentration avgConc_H_lgr2rgl = DryChem::calculateAverage(data.activity[H_index].begin() + leftGraphene_right,
            data.activity[H_index].begin() + rightGraphene_left);

        Concentration avgConc_H_rgr2e
            = DryChem::calculateAverage(data.activity[H_index].begin() + rightGraphene_right, data.activity[H_index].end());

        // Printing
        std::size_t numberStart {path.find("stitch") + 7};
        std::size_t numberEnd {path.find(".rnemd")};

        outputFile << std::setw(4) << (std::stoi(path.substr(numberStart, numberEnd - numberStart))) << ',';

        outputFile << std::setw(12) << params.report.particleFlux << ',' << std::setw(18) << params.report.Jp << ','
                   << std::setw(12)
                   << ((avgConc_cation_b2lgl + avgConc_cation_rgr2b) / 2 - (avgConc_cation_a2rgl - avgConc_cation_lgr2a) / 2)
                   << ',' << std::setw(12)
                   << ((avgConc_anion_b2lgl + avgConc_anion_rgr2b) / 2 - (avgConc_anion_lgr2a - avgConc_anion_a2rgl) / 2)
                   << ',' << std::setw(12) << ((avgConc_O_s2lgl + avgConc_O_rgr2e) / 2 - avgConc_O_lgr2rgl) << ','
                   << std::setw(12) << ((avgConc_H_s2lgl + avgConc_H_rgr2e) / 2 - avgConc_H_lgr2rgl) << '\n';
    }
}
