// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: regionFitting.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:43:08
// Description: Implementation of the pure virtual functions defined in the chargedRNEMDAnalysisMethod class

#include <array>
#include <fstream>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/math.hpp>

#include "../include/regionFitting.hpp"

using namespace PhysicalQuantities;

namespace OpenMD::RNEMD::ChargedRNEMD
{
    void RegionFitting::calculateGradientOfElectrochemicalPotential()
    {
        for (const auto& ion : rnemdParameters->ionicSpecies)
        {
            std::vector< std::array<Force, 2> > temporaryStorageVector;
            std::vector< std::vector<Force> > temporaryFittingParameters;

            for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
            {
                temporaryFittingParameters.push_back(
                    Math::linearLeastSquaresFitting(individualRegionData[region - 1]->rnemdAxis,
                        electrochemicalPotential[ion->getIonIndex()][region - 1]) );

                std::array<Force, 2> temporaryArray { temporaryFittingParameters[region - 1][0],
                                                      temporaryFittingParameters[region - 1][2] };

                temporaryStorageVector.push_back(temporaryArray);
            }

            gradientOfElectrochemicalPotential.push_back(temporaryStorageVector);
            fittingParameters.push_back(temporaryFittingParameters);
        }
    }


    void RegionFitting::printAdditionalRegionHeader(std::ofstream& outputFileStream, int region)
    {
        outputFileStream << "# Region Fitting Parameters:\n";

        for (const auto& ion : rnemdParameters->ionicSpecies)
            outputFileStream << "#   " << ion->getIonName()
                             << ": y = (" << fittingParameters[ion->getIonIndex()][region - 1][0]
                             << " +/- "   << fittingParameters[ion->getIonIndex()][region - 1][2]
                             << ")x + "   << fittingParameters[ion->getIonIndex()][region - 1][1]
                             << "\n";
    }
}
