// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdFile.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/21/2020-14:16:00
// Description: Funtion definitions for the RNEMDFile class

#include <algorithm>
#include <cstddef>
#include <exception>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/errors.hpp>
#include <utils-api/files.hpp>
#include <utils-api/strings.hpp>

#include "rnemdFile.hpp"

using namespace PhysicalQuantities;

namespace ND_Research
{
    RNEMDFile::RNEMDFile(std::string_view FullFileName) : Utilities_API::Files::TextFile{FullFileName}
    {
        try
        {
            try
            {
                // Serves as the current row we are parsing in the rnemd file
                std::size_t row {2};

                setRNEMDBlockParameters(row);
                setRNEMDReportParameters(row);
                setRNEMDData();
                setRNEMDInferredParameters();
            }
            catch (const std::exception& except)
            {
                // Toss the exception back up for program termination and a more verbose message
                throw Utilities_API::Errors::InvalidInputException { "ND-Research",
                    "Could not convert a string value from the file into parameter type using: "
                        + std::string{except.what()} };
            }
        }
        catch (const Utilities_API::Errors::Exception& except)
        {
            except.handleErrorWithMessage();
        }
    }


    void RNEMDFile::setRNEMDBlockParameters(std::size_t& row)
    {
        rnemdParameters->block.exchangeMethod = superMetaDataVector[row++][3];
        rnemdParameters->block.fluxType = superMetaDataVector[row++][3];

        // With non-periodic simulations, no privilegeAxis is printed; "r" will serve as a good placeholder
        if (superMetaDataVector[row][1] == "privilegedAxis")
            rnemdParameters->block.privilegedAxis = superMetaDataVector[row++][3];
        else
            rnemdParameters->block.privilegedAxis = "r";

        rnemdParameters->block.exchangeTime = Time(std::stold(superMetaDataVector[row++][3]));

        std::size_t selectionSize { superMetaDataVector[row].size() };

        for (std::size_t i {4}; i < selectionSize; i +=2)
            rnemdParameters->block.objectSelection.push_back(superMetaDataVector[row][i]);

        ++row;

        if (rnemdParameters->block.privilegedAxis != "r")
        {
            rnemdParameters->block.selectionA[0] = Length(std::stold(superMetaDataVector[row][6]));
            rnemdParameters->block.selectionA[1] = Length(std::stold(superMetaDataVector[row][10]));

            ++row;

            if (superMetaDataVector[row][4] != "none")
            {
                rnemdParameters->inferred.hasSelectionB = true;
                rnemdParameters->block.selectionB[0] = Length(std::stold(superMetaDataVector[row][6]));
                rnemdParameters->block.selectionB[1] = Length(std::stold(superMetaDataVector[row][10]));
            }
        }
        else
        {
            rnemdParameters->block.selectionA[0] = Length(std::stold(superMetaDataVector[row++][6]));
        }

        ++row;

        for (std::size_t i {4}; i < selectionSize; i +=2)
            rnemdParameters->block.outputSelection.push_back(superMetaDataVector[row][i]);

        // The order of outputSelection is reversed before the RNEMD procedure
        std::reverse(rnemdParameters->block.outputSelection.begin(),
            rnemdParameters->block.outputSelection.end());
    }


    void RNEMDFile::setRNEMDReportParameters(std::size_t& row)
    {
        // Account for the lines between block and report sections
        row += 4;

        /* Since the first sections of the rnemd report parameters are consistent between flux types,
            we will use indicies relative to the row set by the block parameters without updating its value */
        rnemdParameters->report.runningTime = Time(superMetaDataVector[row][4]);

        rnemdParameters->report.kineticFlux = MolarEnergyFlux(superMetaDataVector[row + 2][3]);
        rnemdParameters->report.kineticTarget = MolarEnergy(superMetaDataVector[row + 7][3]);
        rnemdParameters->report.kineticExchange = MolarEnergy(superMetaDataVector[row + 11][3]);
        rnemdParameters->report.Jz = MolarEnergyFlux(superMetaDataVector[row + 15][3]);

        for (int i {}; i < 3; ++i)
        {
            rnemdParameters->report.momentumFlux[i] = MomentumFlux(superMetaDataVector[row + 3][i + 4]);
            rnemdParameters->report.momentumTarget[i] = Momentum(superMetaDataVector[row + 8][i + 4]);
            rnemdParameters->report.momentumExchange[i] = Momentum(superMetaDataVector[row + 12][i + 4]);
            rnemdParameters->report.JzP[i] = MomentumFlux(superMetaDataVector[row + 16][i + 4]);

            rnemdParameters->report.angularMomentumFlux[i] = MomentumFlux(superMetaDataVector[row + 4][i + 5]);
            rnemdParameters->report.angularMomentumTarget[i] = Momentum(superMetaDataVector[row + 9][i + 5]);
            rnemdParameters->report.angularMomentumExchange[i] = Momentum(superMetaDataVector[row + 13][i + 5]);
            rnemdParameters->report.JzL[i] = MomentumFlux(superMetaDataVector[row + 17][i + 5]);
        }

        rnemdParameters->report.currentDensity = CurrentDensity(superMetaDataVector[row + 5][4]);

        // Now we can update the value of row and repeat the process
        row += 17;

        if ( (rnemdParameters->block.fluxType == "Single") || (rnemdParameters->block.fluxType == "Current")
                || (rnemdParameters->block.fluxType == "KE+Current") )
        {
            rnemdParameters->report.Jc_total = CurrentDensity(superMetaDataVector[row + 1][5]);
            rnemdParameters->report.Jc_cation = CurrentDensity(superMetaDataVector[row + 2][5]);
            rnemdParameters->report.Jc_anion = CurrentDensity(superMetaDataVector[row + 3][5]);

            rnemdParameters->report.trialCount = std::stoul(superMetaDataVector[row + 5][3]);
            rnemdParameters->report.failTrialCount = std::stoul(superMetaDataVector[row + 6][3]);

            rnemdParameters->inferred.dataFieldLabelIndex = row + 8;
        }
        else
        {
            rnemdParameters->report.trialCount = std::stoul(superMetaDataVector[row + 2][3]);
            rnemdParameters->report.failTrialCount = std::stoul(superMetaDataVector[row + 3][3]);

            rnemdParameters->inferred.dataFieldLabelIndex = row + 5;

            if (rnemdParameters->block.exchangeMethod == "NIVS")
            {
                rnemdParameters->report.failRootCount = std::stoul(superMetaDataVector[row + 4][5]);
                rnemdParameters->inferred.dataFieldLabelIndex = row + 6;
            }
        }
    }


    void RNEMDFile::setRNEMDInferredParameters()
    {
        if (rnemdParameters->block.privilegedAxis != "r")
        {
            rnemdParameters->inferred.slabWidth
                = rnemdParameters->block.selectionA[1] - rnemdParameters->block.selectionA[0];

            rnemdParameters->inferred.numberOfRegions
                = (rnemdParameters->block.fluxType == "Single") ? 2 : 4;

            rnemdParameters->inferred.boxSize
                = allDataFromFile->rnemdAxis.back() + allDataFromFile->rnemdAxis.front();
        }
        else
        {
            rnemdParameters->inferred.slabWidth = rnemdParameters->block.selectionA[0];
            rnemdParameters->inferred.numberOfRegions = 2;
            rnemdParameters->inferred.hasSelectionB = false;

            rnemdParameters->inferred.boxSize
                = allDataFromFile->radius.back() + allDataFromFile->radius.front();
        }

        rnemdParameters->inferred.percentageOfKicksFailed
            = static_cast<double>(rnemdParameters->report.failTrialCount)
                / static_cast<double>(rnemdParameters->report.trialCount) * 100;
    }


    int RNEMDFile::findDataFieldStartLocation(std::string_view dataFieldLabel)
    {
        if ( Utilities_API::Strings::stringFinder(dataFieldLabel,
             metaDataVector[rnemdParameters->inferred.dataFieldLabelIndex]) )
            return metaDataVector[rnemdParameters->inferred.dataFieldLabelIndex].find(dataFieldLabel);

        return std::numeric_limits<int>::max();
    }


    template<typename T>
    std::vector<T> RNEMDFile::parseDataFromFile(int startIndex)
    {
        std::vector<T> PhysicalQuantity;

        for (const auto& vec : superDataVector)
            PhysicalQuantity.push_back( T(vec[startIndex]) );

        return PhysicalQuantity;
    }


    void RNEMDFile::setRNEMDData()
    {
        std::vector< std::pair<std::string, int> > locations;

        if (rnemdParameters->block.privilegedAxis != "z")
            allDataFromFile->dataLabels[0] = rnemdParameters->block.privilegedAxis + "(Angstroms)";

        for (const auto& dataLabel : allDataFromFile->dataLabels)
            locations.push_back( std::make_pair(dataLabel, findDataFieldStartLocation(dataLabel)) );

        std::sort( locations.begin(), locations.end(), [](std::pair<std::string, int>& a,
            std::pair<std::string, int>& b) -> bool { return a.second < b.second; } );

        int startIndex {};

        for (const auto& pair : locations)
        {
            if (pair.second != std::numeric_limits<int>::max())
            {
                int index {pair.second - startIndex - 2};

                if (pair.first == allDataFromFile->dataLabels[0])
                    allDataFromFile->rnemdAxis = parseDataFromFile<Length>(index);

                else if (pair.first == allDataFromFile->dataLabels[1])
                    allDataFromFile->radius = parseDataFromFile<Length>(index);

                else if (pair.first == allDataFromFile->dataLabels[2])
                    allDataFromFile->temperature = parseDataFromFile<Temperature>(index);

                else if (pair.first == allDataFromFile->dataLabels[3])
                    for (int i {}; i < 3 ; ++i)
                        allDataFromFile->velocity[i] = (parseDataFromFile<Velocity>(index + i));

                else if (pair.first == allDataFromFile->dataLabels[4])
                    for (int i {}; i < 3 ; ++i)
                        allDataFromFile->angularVelocity[i] = (parseDataFromFile<Velocity>(index + i));

                else if (pair.first == allDataFromFile->dataLabels[5])
                    allDataFromFile->density = parseDataFromFile<MassDensity>(index);

                else if (pair.first == allDataFromFile->dataLabels[6])
                {
                    // Only include concentrations for atom types that are actually printed out
                    for (std::size_t i {}; i < rnemdParameters->block.outputSelection.size(); ++i)
                        if ( Utilities_API::Strings::stringFinder(rnemdParameters->block.outputSelection[i],
                            metaDataVector[rnemdParameters->inferred.dataFieldLabelIndex]) )
                        {
                            startIndex += (1 + rnemdParameters->block.outputSelection[i].length());
                            allDataFromFile->activity.push_back(parseDataFromFile<Concentration>(index + i));
                        }

                    startIndex += 2;
                }

                else if (pair.first == allDataFromFile->dataLabels[7])
                    for (int i {}; i < 3 ; ++i)
                        allDataFromFile->electricField[i] = (parseDataFromFile<ElectricField>(index + i));

                else if (pair.first == allDataFromFile->dataLabels[8])
                    allDataFromFile->electricPotential = parseDataFromFile<ElectricPotential>(index);

                startIndex += pair.first.length();
            }
        }
    }
}
