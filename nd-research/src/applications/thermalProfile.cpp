// Copyright (c) 2019-2023 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: thermalProfile.cpp
// Author: crdrisko
// Date: 09/06/2023-11:10:48
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

    // Sort the filenames
    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".rnemd")
            paths.insert(dirEntry.path().string());

    std::vector<RNEMDData> inputData;
    std::vector<RNEMDParameters> inputParams;

    int boundaryA_start {}, boundaryA_end {}, boundaryB_start {}, boundaryB_end {};

    for (const auto& path : paths)
    {
        RNEMDFile rnemdFile {path};

        RNEMDData data         = rnemdFile.getRNEMDData();
        RNEMDParameters params = rnemdFile.getRNEMDParameters();

        boundaryA_start += rnemdFile.determineRegionBounds(params.block.selectionA[0]);
        boundaryA_end += rnemdFile.determineRegionBounds(params.block.selectionA[1]);
        boundaryB_start += rnemdFile.determineRegionBounds(params.block.selectionB[0]);
        boundaryB_end += rnemdFile.determineRegionBounds(params.block.selectionB[1]);

        inputData.push_back(data);
        inputParams.push_back(params);
    }

    boundaryA_start /= inputData.size();
    boundaryA_end /= inputData.size();
    boundaryB_start /= inputData.size();
    boundaryB_end /= inputData.size();

    RNEMDData outputData         = inputData[0];
    RNEMDParameters outputParams = inputParams[0];

    for (std::size_t i {1}; i < inputData.size(); ++i)
    {
        for (std::size_t j {}; j < inputData[i].rnemdAxis.size(); ++j)
        {
            outputData.rnemdAxis[j] += inputData[i].rnemdAxis[j];
            outputData.temperature[j] += inputData[i].temperature[j];

            for (std::size_t k {}; k < inputData[i].velocity[j].size(); ++k)
                outputData.velocity[j][k] += inputData[i].velocity[j][k];

            outputData.density[j] += inputData[i].density[j];

            for (std::size_t k {}; k < inputData[i].activity.size(); ++k)
                outputData.activity[k][j] += inputData[i].activity[k][j];
        }
    }

    for (std::size_t i {}; i < outputData.rnemdAxis.size(); ++i)
    {
        outputData.rnemdAxis[i] /= inputData.size();
        outputData.temperature[i] /= inputData.size();

        for (std::size_t j {}; j < outputData.velocity[i].size(); ++j)
            outputData.velocity[i][j] /= inputData.size();

        outputData.density[i] /= inputData.size();

        for (std::size_t j {}; j < outputData.activity.size(); ++j)
            outputData.activity[j][i] /= inputData.size();
    }

    // Calculate Errors
    RNEMDData outputErrors = outputData;

    for (std::size_t bin {}; bin < outputData.rnemdAxis.size(); ++bin)
    {
        // RNEMD Axis
        PhysicalQuantity<Dimensionality<2, 0, 0>> sumAxis {};

        for (std::size_t sample {}; sample < inputData.size(); ++sample)
        {
            Length diff = inputData[sample].rnemdAxis[bin] - outputData.rnemdAxis[bin];

            sumAxis += (diff * diff);
        }

        outputErrors.rnemdAxis[bin] = 1.96 * Math::sqrt(sumAxis / (inputData.size() - 1)) / std::sqrt(inputData.size());

        if (Math::abs(outputErrors.rnemdAxis[bin]) < Length {1e-16})
            outputErrors.rnemdAxis[bin] = Length {};

        // Temperature
        PhysicalQuantity<Dimensionality<0, 0, 0, 0, 2>> sumTemp {};

        for (std::size_t sample {}; sample < inputData.size(); ++sample)
        {
            Temperature diff = inputData[sample].temperature[bin] - outputData.temperature[bin];

            sumTemp += (diff * diff);
        }

        outputErrors.temperature[bin]
            = ((1.96 * Math::sqrt(sumTemp / (inputData.size() - 1))) / std::sqrt(inputData.size()));

        // Velocity
        for (std::size_t elem {}; elem < outputData.velocity[bin].size(); ++elem)
        {
            PhysicalQuantity<Dimensionality<2, 0, -2>> sumVel {};

            for (std::size_t sample {}; sample < inputData.size(); ++sample)
            {
                Velocity diff = inputData[sample].velocity[bin][elem] - outputData.velocity[bin][elem];

                sumVel += (diff * diff);
            }

            outputErrors.velocity[bin][elem]
                = (1.96 * Math::sqrt(sumVel / (inputData.size() - 1))) / std::sqrt(inputData.size());
        }

        // Density
        PhysicalQuantity<Dimensionality<-6, 2, 0>> sumDen {};

        for (std::size_t sample {}; sample < inputData.size(); ++sample)
        {
            MassDensity diff = inputData[sample].density[bin] - outputData.density[bin];

            sumDen += (diff * diff);
        }

        outputErrors.density[bin] = ((1.96 * Math::sqrt(sumDen / (inputData.size() - 1))) / std::sqrt(inputData.size()));

        // Activity
        for (std::size_t sele {}; sele < outputData.activity.size(); ++sele)
        {
            PhysicalQuantity<Dimensionality<-6, 0, 0, 0, 0, 2>> sumConc {};

            for (std::size_t sample {}; sample < inputData.size(); ++sample)
            {
                Concentration diff = inputData[sample].activity[sele][bin] - outputData.activity[sele][bin];

                sumConc += (diff * diff);
            }

            outputErrors.activity[sele][bin]
                = (1.96 * Math::sqrt(sumConc / (inputData.size() - 1))) / std::sqrt(inputData.size());
        }
    }

    // auto dSele1_dz = DryChem::centeredDifferenceMethod(outputData.rnemdAxis, outputData.activity[0]);
    // auto dSele2_dz = DryChem::centeredDifferenceMethod(outputData.rnemdAxis, outputData.activity[1]);

    auto dSele1_dz = DryChem::fivePointStencilMethod(outputData.rnemdAxis, outputData.activity[0]);
    auto dSele2_dz = DryChem::fivePointStencilMethod(outputData.rnemdAxis, outputData.activity[1]);

    std::ofstream outputFile;
    outputFile.open(fileName + ".csv");

    outputFile << "# Z," << std::setw(17) << "Temperature," << std::setw(17) << "[Sele1]," << std::setw(17) << "[Sele2],"
               << std::setw(17) << "d[Sele1]_dz," << std::setw(17) << "d[Sele2]_dz," << std::setw(17) << "95% CI Temp,"
               << std::setw(17) << "95% CI [Sele1]," << std::setw(17) << "95% CI [Sele2]\n";

    for (std::size_t bin {}; bin < outputData.rnemdAxis.size(); ++bin)
    {
        outputFile << outputData.rnemdAxis[bin] << ',' << std::setw(14) << outputData.temperature[bin] << ','
                   << std::setw(14) << outputData.activity[0][bin] << ',' << std::setw(14) << outputData.activity[1][bin]
                   << ',' << std::setw(14) << dSele1_dz[bin] << ',' << std::setw(14) << dSele2_dz[bin] << ','
                   << std::setw(14) << outputErrors.temperature[bin] << ',' << std::setw(14) << outputErrors.activity[0][bin]
                   << ',' << std::setw(14) << outputErrors.activity[1][bin] << '\n';
    }

    std::vector<Temperature> temperature_B2A {outputData.temperature.begin() + boundaryB_end,
        outputData.temperature.begin() + boundaryA_start};

    std::vector<Temperature> temperature_A2B {outputData.temperature.begin() + boundaryA_end,
        outputData.temperature.begin() + boundaryB_start};

    std::vector<ConcentrationGradient> dSele1_dz_B2A {dSele1_dz.begin() + boundaryB_end,
        dSele1_dz.begin() + boundaryA_start};

    std::vector<ConcentrationGradient> dSele1_dz_A2B {dSele1_dz.begin() + boundaryA_end,
        dSele1_dz.begin() + boundaryB_start};

    std::vector<ConcentrationGradient> dSele2_dz_B2A {dSele2_dz.begin() + boundaryB_end,
        dSele2_dz.begin() + boundaryA_start};

    std::vector<ConcentrationGradient> dSele2_dz_A2B {dSele2_dz.begin() + boundaryA_end,
        dSele2_dz.begin() + boundaryB_start};

    std::ofstream outputFile2;
    outputFile2.open(fileName + "2.csv");

    outputFile2 << "# Temperature B->A," << std::setw(17) << "d[Sele1]_dz B->A," << std::setw(17) << "d[Sele2]_dz B->A"
                << std::setw(17) << "Temperature A->B," << std::setw(17) << "d[Sele1]_dz A->B," << std::setw(17)
                << "d[Sele2]_dz A->B\n";

    if (temperature_B2A.size() == temperature_A2B.size())
    {
        for (std::size_t bin {1}; bin < temperature_B2A.size() - 1; ++bin)
        {
            outputFile2 << std::setw(14) << temperature_B2A[bin] << std::setw(14) << dSele1_dz_B2A[bin] << std::setw(14)
                        << dSele2_dz_B2A[bin] << std::setw(14) << temperature_A2B[bin] << std::setw(14) << dSele1_dz_A2B[bin]
                        << std::setw(14) << dSele2_dz_A2B[bin] << '\n';
        }
    }
    else
    {
        std::cout << "The regions between RNEMD slabs A and B were different sizes.\n";
        std::exit(EXIT_FAILURE);
    }

    // Temperature fits
    auto Tz_B2A = DryChem::linearLeastSquaresFitting(outputData.rnemdAxis.begin() + boundaryB_end,
        outputData.rnemdAxis.begin() + boundaryA_start,
        outputData.temperature.begin() + boundaryB_end,
        outputData.temperature.begin() + boundaryA_start);

    auto Tz_A2B = DryChem::linearLeastSquaresFitting(outputData.rnemdAxis.begin() + boundaryA_end,
        outputData.rnemdAxis.begin() + boundaryB_start,
        outputData.temperature.begin() + boundaryA_end,
        outputData.temperature.begin() + boundaryB_start);

    std::cout << "B->A: T(z) = " << Tz_B2A.slope << " z + " << Tz_B2A.intercept << "\nA->B: T(z) = " << Tz_A2B.slope
              << " z + " << Tz_A2B.intercept << "\n";

    // Concentration fits
    auto cz_sele1_B2A = DryChem::quadraticLeastSquaresFitting(outputData.rnemdAxis.begin() + boundaryB_end,
        outputData.rnemdAxis.begin() + boundaryA_start,
        outputData.activity[0].begin() + boundaryB_end,
        outputData.activity[0].begin() + boundaryA_start);

    auto cz_sele1_A2B = DryChem::quadraticLeastSquaresFitting(outputData.rnemdAxis.begin() + boundaryA_end,
        outputData.rnemdAxis.begin() + boundaryB_start,
        outputData.activity[0].begin() + boundaryA_end,
        outputData.activity[0].begin() + boundaryB_start);

    std::cout << "B->A: c_1(z) = " << cz_sele1_B2A.a << " z^2 + " << cz_sele1_B2A.b << " z + " << cz_sele1_B2A.c << '\n'
              << "A->B: c_1(z) = " << cz_sele1_A2B.a << " z^2 + " << cz_sele1_A2B.b << " z + " << cz_sele1_A2B.c << '\n';

    std::cout << "B->A: dc1_dz = " << (2 * cz_sele1_B2A.a) << " z + " << cz_sele1_B2A.b << '\n'
              << "A->B: dc1_dz = " << (2 * cz_sele1_A2B.a) << " z + " << cz_sele1_A2B.b << '\n';

    auto cz_sele2_B2A = DryChem::quadraticLeastSquaresFitting(outputData.rnemdAxis.begin() + boundaryB_end,
        outputData.rnemdAxis.begin() + boundaryA_start,
        outputData.activity[1].begin() + boundaryB_end,
        outputData.activity[1].begin() + boundaryA_start);

    auto cz_sele2_A2B = DryChem::quadraticLeastSquaresFitting(outputData.rnemdAxis.begin() + boundaryA_end,
        outputData.rnemdAxis.begin() + boundaryB_start,
        outputData.activity[1].begin() + boundaryA_end,
        outputData.activity[1].begin() + boundaryB_start);

    std::cout << "B->A: c_2(z) = " << cz_sele2_B2A.a << " z^2 + " << cz_sele2_B2A.b << " z + " << cz_sele2_B2A.c << '\n'
              << "A->B: c_2(z) = " << cz_sele2_A2B.a << " z^2 + " << cz_sele2_A2B.b << " z + " << cz_sele2_A2B.c << '\n';

    std::cout << "B->A: dc2_dz = " << (2 * cz_sele2_B2A.a) << " z + " << cz_sele2_B2A.b << '\n'
              << "A->B: dc2_dz = " << (2 * cz_sele2_A2B.a) << " z + " << cz_sele2_A2B.b << '\n';
}