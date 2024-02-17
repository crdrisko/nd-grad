// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: soretEffects.cpp
// Author: crdrisko
// Date: 11/21/2023-07:43:08
// Description:

#include <cmath>
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

using SoretCoefficient = PhysicalQuantity<Dimensionality<0, 0, 0, 0, -1>>;

void calculateSoretCoefficient(const std::set<std::string>& paths);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <kinetic_path>\n";
        return EXIT_FAILURE;
    }

    // Sort the kinetic filenames
    std::set<std::string> kineticPaths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".rnemd")
            kineticPaths.insert(dirEntry.path().string());

    calculateSoretCoefficient(kineticPaths);
}

void calculateSoretCoefficient(const std::set<std::string>& paths)
{
    std::vector<RNEMDData> inputData;
    std::vector<RNEMDParameters> inputParams;

    for (const auto& path : paths)
    {
        RNEMDFile rnemdFile {path};

        RNEMDData data         = rnemdFile.getRNEMDData();
        RNEMDParameters params = rnemdFile.getRNEMDParameters();

        inputData.push_back(data);
        inputParams.push_back(params);
    }

    RNEMDData outputData         = inputData[0];
    RNEMDParameters outputParams = inputParams[0];

    for (std::size_t i {1}; i < inputParams.size(); ++i)
    {
        outputParams.report.kineticExchange += inputParams[i].report.kineticExchange;
        outputParams.report.particleExchange += inputParams[i].report.particleExchange;
        outputParams.report.Jz += inputParams[i].report.Jz;
        outputParams.report.Jp += inputParams[i].report.Jp;
        outputParams.report.failTrialCount += inputParams[i].report.failTrialCount;

        outputParams.inferred.boundaryA_start += inputParams[i].inferred.boundaryA_start;
        outputParams.inferred.boundaryA_end += inputParams[i].inferred.boundaryA_end;
        outputParams.inferred.boundaryB_start += inputParams[i].inferred.boundaryB_start;
        outputParams.inferred.boundaryB_end += inputParams[i].inferred.boundaryB_end;
    }

    outputParams.report.kineticExchange /= inputParams.size();
    outputParams.report.particleExchange /= inputParams.size();
    outputParams.report.Jz /= inputParams.size();
    outputParams.report.Jp /= inputParams.size();
    outputParams.report.failTrialCount /= inputParams.size();

    outputParams.inferred.boundaryA_start /= inputParams.size();
    outputParams.inferred.boundaryA_end /= inputParams.size();
    outputParams.inferred.boundaryB_start /= inputParams.size();
    outputParams.inferred.boundaryB_end /= inputParams.size();

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

    std::vector<Length> rnemdAxis {outputData.rnemdAxis.begin() + outputParams.inferred.boundaryB_end,
        outputData.rnemdAxis.begin() + outputParams.inferred.boundaryA_start};

    std::vector<Temperature> temperature {outputData.temperature.begin() + outputParams.inferred.boundaryB_end,
        outputData.temperature.begin() + outputParams.inferred.boundaryA_start};

    std::vector<Temperature> temperature_A2B {outputData.temperature.begin() + outputParams.inferred.boundaryA_end,
        outputData.temperature.begin() + outputParams.inferred.boundaryB_start};

    std::vector<Concentration> sele1 {outputData.activity[0].begin() + outputParams.inferred.boundaryB_end,
        outputData.activity[0].begin() + outputParams.inferred.boundaryA_start};

    std::vector<Concentration> sele1_A2B {outputData.activity[0].begin() + outputParams.inferred.boundaryA_end,
        outputData.activity[0].begin() + outputParams.inferred.boundaryB_start};

    std::vector<Concentration> sele2 {outputData.activity[1].begin() + outputParams.inferred.boundaryB_end,
        outputData.activity[1].begin() + outputParams.inferred.boundaryA_start};

    std::vector<Concentration> sele2_A2B {outputData.activity[1].begin() + outputParams.inferred.boundaryA_end,
        outputData.activity[1].begin() + outputParams.inferred.boundaryB_start};

    std::vector<Temperature> temp_avg;
    std::vector<Concentration> sele1_avg, sele2_avg;

    for (std::size_t fbin {}, rbin {rnemdAxis.size() - 1}; fbin < rnemdAxis.size(); ++fbin)
    {
        temp_avg.push_back(0.5 * (temperature[fbin] + temperature_A2B[rbin]));
        sele1_avg.push_back(0.5 * (sele1[fbin] + sele1_A2B[rbin]));
        sele2_avg.push_back(0.5 * (sele2[fbin] + sele2_A2B[rbin]));

        rbin--;
    }

    auto Tz = DryChem::linearLeastSquaresFitting(rnemdAxis.begin(), rnemdAxis.end(), temp_avg.begin(), temp_avg.end());

    auto cz_sele1
        = DryChem::linearLeastSquaresFitting(rnemdAxis.begin(), rnemdAxis.end(), sele1_avg.begin(), sele1_avg.end());

    auto cz_sele2
        = DryChem::linearLeastSquaresFitting(rnemdAxis.begin(), rnemdAxis.end(), sele2_avg.begin(), sele2_avg.end());

    auto SoretCoefficient1 = -((cz_sele1.slope * 1000.0_L / 1e30)
                               / (Tz.slope * (3000 * 1.0_mol / (348'592.791 * Constants::avogadrosNumber)) * 0.5));

    auto SoretCoefficient2 = -((cz_sele2.slope * 1000.0_L / 1e30)
                               / (Tz.slope * (3000 * 1.0_mol / (348'592.791 * Constants::avogadrosNumber)) * 0.5));

    std::cout << SoretCoefficient1 << '\t' << SoretCoefficient2 << '\n';
}
