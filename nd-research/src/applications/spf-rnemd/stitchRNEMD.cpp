// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: stitchRNEMD.cpp
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

void writeXMGraceOutput(const std::string& fileName, const RNEMDData& data, const RNEMDData& errors);

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

    std::vector<RNEMDData> inputData;
    std::vector<RNEMDParameters> inputParams;

    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".rnemd")
            paths.insert(dirEntry.path().string());

    for (const auto& path : paths)
    {
        RNEMDFile rnemdFile {path};

        inputData.push_back(rnemdFile.getRNEMDData());
        inputParams.push_back(rnemdFile.getRNEMDParameters());
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
    }

    outputParams.report.kineticExchange /= inputParams.size();
    outputParams.report.particleExchange /= inputParams.size();
    outputParams.report.Jp /= inputParams.size();
    outputParams.report.Jp /= inputParams.size();
    outputParams.report.failTrialCount /= inputParams.size();

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

        outputErrors.rnemdAxis[bin] = 1.96 * Math::sqrt(sumAxis / inputData.size()) / std::sqrt(inputData.size());

        if (Math::abs(outputErrors.rnemdAxis[bin]) < Length {1e-16})
            outputErrors.rnemdAxis[bin] = Length {};

        // Temperature
        PhysicalQuantity<Dimensionality<0, 0, 0, 0, 2>> sumTemp {};

        for (std::size_t sample {}; sample < inputData.size(); ++sample)
        {
            Temperature diff = inputData[sample].temperature[bin] - outputData.temperature[bin];

            sumTemp += (diff * diff);
        }

        outputErrors.temperature[bin] = ((1.96 * Math::sqrt(sumTemp / inputData.size())) / std::sqrt(inputData.size()));

        // Velocity
        for (std::size_t elem {}; elem < outputData.velocity[bin].size(); ++elem)
        {
            PhysicalQuantity<Dimensionality<2, 0, -2>> sumVel {};

            for (std::size_t sample {}; sample < inputData.size(); ++sample)
            {
                Velocity diff = inputData[sample].velocity[bin][elem] - outputData.velocity[bin][elem];

                sumVel += (diff * diff);
            }

            outputErrors.velocity[bin][elem] = (1.96 * Math::sqrt(sumVel / inputData.size())) / std::sqrt(inputData.size());
        }

        // Density
        PhysicalQuantity<Dimensionality<-6, 2, 0>> sumDen {};

        for (std::size_t sample {}; sample < inputData.size(); ++sample)
        {
            MassDensity diff = inputData[sample].density[bin] - outputData.density[bin];

            sumDen += (diff * diff);
        }

        outputErrors.density[bin] = ((1.96 * Math::sqrt(sumDen / inputData.size())) / std::sqrt(inputData.size()));

        // Activity
        for (std::size_t sele {}; sele < outputData.activity.size(); ++sele)
        {
            PhysicalQuantity<Dimensionality<-6, 0, 0, 0, 0, 2>> sumConc {};

            for (std::size_t sample {}; sample < inputData.size(); ++sample)
            {
                Concentration diff = inputData[sample].activity[sele][bin] - outputData.activity[sele][bin];

                sumConc += (diff * diff);
            }

            outputErrors.activity[sele][bin] = (1.96 * Math::sqrt(sumConc / inputData.size())) / std::sqrt(inputData.size());
        }
    }

    RNEMDFile outputFile {outputData, outputErrors, outputParams};

    outputFile.writeRNEMDFile(fileName + ".rnemd");
    writeXMGraceOutput(fileName + ".txt", outputData, outputErrors);
}

void writeXMGraceOutput(const std::string& fileName, const RNEMDData& data, const RNEMDData& errors)
{
    std::ofstream outputFileStream;
    outputFileStream.open(fileName);

    outputFileStream.precision(8);

    // XMGrace Printouts
    std::size_t numGraphs = 2;
    std::size_t numSets   = 1;

    for (std::size_t graph {}; graph < numGraphs; ++graph)
    {
        for (std::size_t set {}; set < numSets; ++set)
        {
            outputFileStream << "@target G" << graph << ".S" << set << "\n"
                             << "@type xydy\n";

            for (std::size_t bin {}; bin < data.rnemdAxis.size(); ++bin)
            {
                outputFileStream << data.rnemdAxis[bin] << '\t' << data.activity[graph][bin] << '\t'
                                 << errors.activity[graph][bin] << '\n';
            }

            outputFileStream << "&\n";
        }
    }
}
