// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: regionDifference.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:43:14
// Description: Implementation of the pure virtual functions defined in the chargedRNEMDAnalysisMethod class

#include <array>
#include <cmath>
#include <fstream>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/math.hpp>

#include "../include/regionDifference.hpp"

using namespace PhysicalQuantities;

namespace OpenMD::RNEMD::ChargedRNEMD
{
    void RegionDifference::calculateGradientOfElectrochemicalPotential()
    {
        for (const auto& ion : rnemdParameters->ionicSpecies)
        {
            std::vector< std::array<Force, 2> > temporaryStorageVector;
            std::vector< std::vector<Force> > temporaryFittingParameters;

            Energy avgElectrochemicalPotential_region2
                = Math::calculateAverage(electrochemicalPotential[ion->getIonIndex()][1]);

            Energy stdDevElectrochemicalPotential_region2
                = Math::calculateStandardDeviation(electrochemicalPotential[ion->getIonIndex()][1]);

            Energy avgElectrochemicalPotential_region4
                = Math::calculateAverage(electrochemicalPotential[ion->getIonIndex()][3]);

            Energy stdDevElectrochemicalPotential_region4
                = Math::calculateStandardDeviation(electrochemicalPotential[ion->getIonIndex()][3]);

            for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
            {
                if (region == 1 || region == 3)
                {
                    temporaryFittingParameters.push_back(
                        Math::linearLeastSquaresFitting(individualRegionData[region - 1]->rnemdAxis,
                            electrochemicalPotential[ion->getIonIndex()][region - 1]) );

                    std::array<Force, 2> temporaryArray { temporaryFittingParameters[region - 1][0],
                                                          temporaryFittingParameters[region - 1][2] };

                    temporaryStorageVector.push_back(temporaryArray);
                }
                else
                {
                    temporaryFittingParameters.push_back(temporaryFittingParameters[region - 2]);

                    std::array<Force, 2> temporaryArray;

                    temporaryArray[0] = (avgElectrochemicalPotential_region2 - avgElectrochemicalPotential_region4)
                        / rnemdParameters->inferred->slabWidth;

                    temporaryArray[1] = Energy( std::sqrt( (stdDevElectrochemicalPotential_region2.getMagnitude()
                        / electrochemicalPotential[ion->getIonIndex()][1].size()) + (stdDevElectrochemicalPotential_region4.getMagnitude()
                        / electrochemicalPotential[ion->getIonIndex()][3].size()) ) ) / rnemdParameters->inferred->slabWidth;

                    temporaryStorageVector.push_back(temporaryArray);
                }
            }

            gradientOfElectrochemicalPotential.push_back(temporaryStorageVector);

            if ( !temporaryFittingParameters.empty() )
                fittingParameters.push_back(temporaryFittingParameters);
        }
    }


    void RegionDifference::printAdditionalRegionHeader(std::ofstream& outputFileStream, int region)
    {
        if (region == 1 || region == 3)
        {
            outputFileStream << "# Region Fitting Parameters:\n";

            for (const auto& ion : rnemdParameters->ionicSpecies)
                outputFileStream << "#   " << ion->getIonName()
                                 << ": y = (" << fittingParameters[ion->getIonIndex()][region - 1][0]
                                 << " +/- "   << fittingParameters[ion->getIonIndex()][region - 1][2]
                                 << ")x + "   << fittingParameters[ion->getIonIndex()][region - 1][1]
                                 << "\n";
        }
        else
        {
            outputFileStream << "# Region Averaging Parameters:\n";

            for (const auto& ion : rnemdParameters->ionicSpecies)
                outputFileStream << "#   " << ion->getIonName()
                                 << ": "    << gradientOfElectrochemicalPotential[ion->getIonIndex()][region - 1][0]
                                 << " +/- " << gradientOfElectrochemicalPotential[ion->getIonIndex()][region - 1][1]
                                 << "\n";
        }
    }
}
