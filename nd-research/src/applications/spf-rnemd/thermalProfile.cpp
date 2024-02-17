// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
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
using namespace Literals;
using namespace ND_Research;

namespace fs = std::filesystem;

using SoretCoefficient = PhysicalQuantity<Dimensionality<0, 0, 0, 0, -1>>;

void generatePureDataFile(const std::string& fileName, const RNEMDData& data, const RNEMDData& errors);
void printFile2(const std::string& fileName, const RNEMDData& data, const RNEMDData& errors, const RNEMDParameters& params);
void generateFitDataFiles(const std::string& fileName, const RNEMDData& data, const RNEMDParameters& params);

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
        outputParams.report.particleExchange += inputParams[i].report.particleExchange;
        outputParams.report.Jp += inputParams[i].report.Jp;
        outputParams.report.failTrialCount += inputParams[i].report.failTrialCount;

        outputParams.inferred.boundaryA_start += inputParams[i].inferred.boundaryA_start;
        outputParams.inferred.boundaryA_end += inputParams[i].inferred.boundaryA_end;
        outputParams.inferred.boundaryB_start += inputParams[i].inferred.boundaryB_start;
        outputParams.inferred.boundaryB_end += inputParams[i].inferred.boundaryB_end;
    }

    outputParams.report.particleExchange /= inputParams.size();
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

            outputErrors.activity[sele][bin] = Math::sqrt(sumConc / (inputData.size() - 1));
        }
    }

    generatePureDataFile(fileName, outputData, outputErrors);
    printFile2(fileName, outputData, outputErrors, outputParams);
    // generateFitDataFiles(fileName, outputData, outputParams);
}

void generatePureDataFile(const std::string& fileName, const RNEMDData& data, const RNEMDData& errors)
{
    auto dSele1_dz_v1 = DryChem::centeredDifferenceMethod(data.rnemdAxis, data.activity[0]);
    auto dSele2_dz_v1 = DryChem::centeredDifferenceMethod(data.rnemdAxis, data.activity[1]);

    std::vector<ConcentrationGradient> errors_dSele1_dz(data.rnemdAxis.size());
    std::vector<ConcentrationGradient> errors_dSele2_dz(data.rnemdAxis.size());

    std::ofstream outputFile;
    outputFile.open(fileName + ".csv");

    auto dx          = data.rnemdAxis[1] - data.rnemdAxis[0];
    std::size_t last = data.rnemdAxis.size() - 1;

    for (std::size_t bin {1}; bin < last; ++bin)
    {
        errors_dSele1_dz[bin] = Math::sqrt((errors.activity[0][bin + 1] * errors.activity[0][bin + 1])
                                           + (errors.activity[0][bin - 1] * errors.activity[0][bin - 1]))
                                / (2 * dx);
        errors_dSele2_dz[bin] = Math::sqrt((errors.activity[1][bin + 1] * errors.activity[1][bin + 1])
                                           + (errors.activity[1][bin - 1] * errors.activity[1][bin - 1]))
                                / (2 * dx);
    }

    errors_dSele1_dz[0]
        = Math::sqrt((errors.activity[0][1] * errors.activity[0][1]) + (errors.activity[0][0] * errors.activity[0][0])) / dx;
    errors_dSele2_dz[0]
        = Math::sqrt((errors.activity[1][1] * errors.activity[1][1]) + (errors.activity[1][0] * errors.activity[1][0])) / dx;

    errors_dSele1_dz[last] = Math::sqrt((errors.activity[0][last] * errors.activity[0][last])
                                        + (errors.activity[0][last - 1] * errors.activity[0][last - 1]))
                             / dx;
    errors_dSele2_dz[last] = Math::sqrt((errors.activity[1][last] * errors.activity[1][last])
                                        + (errors.activity[1][last - 1] * errors.activity[1][last - 1]))
                             / dx;

    outputFile << "# Z," << std::setw(17) << "Temperature," << std::setw(17) << "[Sele1]," << std::setw(17) << "[Sele2],"
               << std::setw(17) << "d[Sele1]_dz," << std::setw(17) << "d[Sele2]_dz," << std::setw(17) << "95% CI Temp,"
               << std::setw(17) << "95% CI [Sele1]," << std::setw(17) << "95% CI [Sele2]\n";

    for (std::size_t bin {}; bin < data.rnemdAxis.size(); ++bin)
    {
        outputFile << data.rnemdAxis[bin] << ',' << std::setw(14) << data.temperature[bin] << ',' << std::setw(14)
                   << data.activity[0][bin] << ',' << std::setw(14) << data.activity[1][bin] << ',' << std::setw(14)
                   << dSele1_dz_v1[bin] << ',' << std::setw(14) << dSele2_dz_v1[bin] << ',' << std::setw(14)
                   << errors.temperature[bin] << ',' << std::setw(14) << errors.activity[0][bin] << ',' << std::setw(14)
                   << errors.activity[1][bin] << ',' << std::setw(14) << errors_dSele1_dz[bin] << ',' << std::setw(14)
                   << errors_dSele2_dz[bin] << '\n';
    }
}

void printFile2(const std::string& fileName, const RNEMDData& data, const RNEMDData& errors, const RNEMDParameters& params)
{
    std::vector<Length> rnemdAxis {data.rnemdAxis.begin() + params.inferred.boundaryB_end,
        data.rnemdAxis.begin() + params.inferred.boundaryA_start};

    std::vector<Temperature> temperature {data.temperature.begin() + params.inferred.boundaryB_end,
        data.temperature.begin() + params.inferred.boundaryA_start};

    std::vector<Temperature> temperature_A2B {data.temperature.begin() + params.inferred.boundaryA_end,
        data.temperature.begin() + params.inferred.boundaryB_start};

    std::vector<Concentration> sele1 {data.activity[0].begin() + params.inferred.boundaryB_end,
        data.activity[0].begin() + params.inferred.boundaryA_start};

    std::vector<Concentration> sele1_A2B {data.activity[0].begin() + params.inferred.boundaryA_end,
        data.activity[0].begin() + params.inferred.boundaryB_start};

    std::vector<Concentration> sele2 {data.activity[1].begin() + params.inferred.boundaryB_end,
        data.activity[1].begin() + params.inferred.boundaryA_start};

    std::vector<Concentration> sele2_A2B {data.activity[1].begin() + params.inferred.boundaryA_end,
        data.activity[1].begin() + params.inferred.boundaryB_start};

    std::vector<Temperature> temp_avg;
    std::vector<Concentration> sele1_avg, sele2_avg;

    for (std::size_t fbin {}, rbin {rnemdAxis.size() - 1}; fbin < rnemdAxis.size(); ++fbin)
    {
        temp_avg.push_back(0.5 * (temperature[fbin] + temperature_A2B[rbin]));
        sele1_avg.push_back(0.5 * (sele1[fbin] + sele1_A2B[rbin]));
        sele2_avg.push_back(0.5 * (sele2[fbin] + sele2_A2B[rbin]));

        rbin--;
    }

    std::vector<ConcentrationGradient> errors_dSele1_dz(data.rnemdAxis.size());
    std::vector<ConcentrationGradient> errors_dSele2_dz(data.rnemdAxis.size());

    auto dx          = data.rnemdAxis[1] - data.rnemdAxis[0];
    std::size_t last = data.rnemdAxis.size() - 1;

    for (std::size_t bin {1}; bin < last; ++bin)
    {
        errors_dSele1_dz[bin] = Math::sqrt((errors.activity[0][bin + 1] * errors.activity[0][bin + 1])
                                           + (errors.activity[0][bin - 1] * errors.activity[0][bin - 1]))
                                / (2 * dx);
        errors_dSele2_dz[bin] = Math::sqrt((errors.activity[1][bin + 1] * errors.activity[1][bin + 1])
                                           + (errors.activity[1][bin - 1] * errors.activity[1][bin - 1]))
                                / (2 * dx);
    }

    auto Tz = DryChem::linearLeastSquaresFitting(rnemdAxis.begin(), rnemdAxis.end(), temp_avg.begin(), temp_avg.end());

    auto dSele1_avg_dz = DryChem::centeredDifferenceMethod(rnemdAxis, sele1_avg, false);

    const auto ConversionFactor = 10 * (1000.0 * 1.0_mol / Constants::avogadrosNumber) / 1.0e-27;

    std::ofstream outputFile2;
    outputFile2.open(fileName + "3.csv");

    SoretCoefficient sT {0.00364509};

    for (std::size_t bin {1}; bin < rnemdAxis.size() - 1; ++bin)
    {
        Concentration c_t = sele1_avg[bin] + sele2_avg[bin];

        DimensionlessQuantity x_1 = sele1_avg[bin] / c_t;
        DimensionlessQuantity x_2 = sele2_avg[bin] / c_t;

        auto D = -(x_2 * params.report.Jp) / (sele2_avg[bin] * x_1 * x_2 * sT * Tz.slope + dSele1_avg_dz[bin - 1]);


        outputFile2 << rnemdAxis[bin] << std::setw(14) << temp_avg[bin] << std::setw(14) << sele1_avg[bin] << std::setw(14)
                    << dSele1_avg_dz[bin - 1] << std::setw(14) << D * ConversionFactor << std::setw(14)
                    << (D * D) / (x_2 * params.report.Jp) * errors_dSele1_dz[bin] * ConversionFactor << '\n';
    }

    /* auto Tz = DryChem::linearLeastSquaresFitting(rnemdAxis.begin(), rnemdAxis.end(), temp_avg.begin(), temp_avg.end());

    auto cz_sele1
        = DryChem::quadraticLeastSquaresFitting(rnemdAxis.begin(), rnemdAxis.end(), sele1_avg.begin(), sele1_avg.end());

    std::ofstream outputFile3;
    outputFile3.open(fileName + "_fit.csv");

    outputFile3 << "# Temperature B->A," << std::setw(17) << "D1(T) B->A," << std::setw(17) << "Temperature A->B,"
                << std::setw(17) << "D1(T) A->B\n";

    for (std::size_t bin {}; bin < temp_avg.size(); ++bin)
    {
        outputFile3 << std::setw(14) << temp_avg[bin] << std::setw(14)
                    << -(sele2_avg[bin] / (sele1_avg[bin] + sele2_avg[bin])) * params.report.Jp
                           / ((2 * cz_sele1.a) * ((temp_avg[bin] - Tz.intercept) / Tz.slope) + cz_sele1.b) * ConversionFactor
                    << '\n';
    } */
}

void generateFitDataFiles(const std::string& fileName, const RNEMDData& data, const RNEMDParameters& params)
{
    std::vector<Temperature> temperature_B2A {data.temperature.begin() + params.inferred.boundaryB_end,
        data.temperature.begin() + params.inferred.boundaryA_start};

    std::vector<Temperature> temperature_A2B {data.temperature.begin() + params.inferred.boundaryA_end,
        data.temperature.begin() + params.inferred.boundaryB_start};

    // Temperature fits
    auto Tz_B2A = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryB_end,
        data.rnemdAxis.begin() + params.inferred.boundaryA_start,
        data.temperature.begin() + params.inferred.boundaryB_end,
        data.temperature.begin() + params.inferred.boundaryA_start);

    auto Tz_A2B = DryChem::linearLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryA_end,
        data.rnemdAxis.begin() + params.inferred.boundaryB_start,
        data.temperature.begin() + params.inferred.boundaryA_end,
        data.temperature.begin() + params.inferred.boundaryB_start);

    std::cout << "B->A: T(z) = " << Tz_B2A.slope << " z + " << Tz_B2A.intercept << "\nA->B: T(z) = " << Tz_A2B.slope
              << " z + " << Tz_A2B.intercept << "\n";

    // Concentration fits
    auto cz_sele1_B2A = DryChem::quadraticLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryB_end,
        data.rnemdAxis.begin() + params.inferred.boundaryA_start,
        data.activity[0].begin() + params.inferred.boundaryB_end,
        data.activity[0].begin() + params.inferred.boundaryA_start);

    auto cz_sele1_A2B = DryChem::quadraticLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryA_end,
        data.rnemdAxis.begin() + params.inferred.boundaryB_start,
        data.activity[0].begin() + params.inferred.boundaryA_end,
        data.activity[0].begin() + params.inferred.boundaryB_start);

    std::cout << "B->A: c_1(z) = " << cz_sele1_B2A.a << " z^2 + " << cz_sele1_B2A.b << " z + " << cz_sele1_B2A.c << '\n'
              << "A->B: c_1(z) = " << cz_sele1_A2B.a << " z^2 + " << cz_sele1_A2B.b << " z + " << cz_sele1_A2B.c << '\n';

    std::cout << "B->A: dc1_dz = " << (2 * cz_sele1_B2A.a) << " z + " << cz_sele1_B2A.b << '\n'
              << "A->B: dc1_dz = " << (2 * cz_sele1_A2B.a) << " z + " << cz_sele1_A2B.b << '\n';

    auto cz_sele2_B2A = DryChem::quadraticLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryB_end,
        data.rnemdAxis.begin() + params.inferred.boundaryA_start,
        data.activity[1].begin() + params.inferred.boundaryB_end,
        data.activity[1].begin() + params.inferred.boundaryA_start);

    auto cz_sele2_A2B = DryChem::quadraticLeastSquaresFitting(data.rnemdAxis.begin() + params.inferred.boundaryA_end,
        data.rnemdAxis.begin() + params.inferred.boundaryB_start,
        data.activity[1].begin() + params.inferred.boundaryA_end,
        data.activity[1].begin() + params.inferred.boundaryB_start);

    std::cout << "B->A: c_2(z) = " << cz_sele2_B2A.a << " z^2 + " << cz_sele2_B2A.b << " z + " << cz_sele2_B2A.c << '\n'
              << "A->B: c_2(z) = " << cz_sele2_A2B.a << " z^2 + " << cz_sele2_A2B.b << " z + " << cz_sele2_A2B.c << '\n';

    std::cout << "B->A: dc2_dz = " << (2 * cz_sele2_B2A.a) << " z + " << cz_sele2_B2A.b << '\n'
              << "A->B: dc2_dz = " << (2 * cz_sele2_A2B.a) << " z + " << cz_sele2_A2B.b << '\n';

    const auto ConversionFactor = (1000.0 * 1.0_mol / Constants::avogadrosNumber) / 1.0e-27;

    std::ofstream outputFile3;
    outputFile3.open(fileName + "_fit.csv");

    outputFile3 << "# Temperature B->A," << std::setw(17) << "D1(T) B->A," << std::setw(17) << "Temperature A->B,"
                << std::setw(17) << "D1(T) A->B\n";

    if (temperature_B2A.size() == temperature_A2B.size())
    {
        for (std::size_t bin {}; bin < temperature_B2A.size(); ++bin)
        {
            outputFile3 << std::setw(14) << temperature_B2A[bin] << std::setw(14)
                        << -0.5 * params.report.Jp
                               / ((2 * cz_sele1_B2A.a) * ((temperature_B2A[bin] - Tz_B2A.intercept) / Tz_B2A.slope)
                                   + cz_sele1_B2A.b)
                               * ConversionFactor * 10
                        << std::setw(14) << temperature_A2B[bin] << std::setw(14)
                        << -0.5 * params.report.Jp
                               / ((2 * cz_sele1_A2B.a) * ((temperature_A2B[bin] - Tz_A2B.intercept) / Tz_A2B.slope)
                                   + cz_sele1_A2B.b)
                               * ConversionFactor * 10
                        << '\n';
        }
    }
    else
    {
        std::cout << "The regions between RNEMD slabs A and B were different sizes.\n";
        std::exit(EXIT_FAILURE);
    }
}
