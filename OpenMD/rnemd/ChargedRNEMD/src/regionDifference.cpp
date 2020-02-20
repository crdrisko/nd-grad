// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: regionDifference.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:43:14
// Description: Implementation of the pure virtual functions defined in the chargedRNEMDAnalysisMethod class

#include "../include/regionDifference.hpp"

using std::vector;
using namespace Utilities_API::PhysicalQuantities;

namespace OpenMD::RNEMD::ChargedRNEMD
{
    void RegionDifference::calculateGradientOfElectrochemicalPotential()
    {
        for (const auto& ion : rnemdParameters->ionicSpecies)
        {
            std::vector<Force> temporaryStorageVector;
            std::vector< std::map<std::string, long double> > temporaryFittingParameters;

            Energy avgElectrochemicalPotential_region2
                = Mathematics::mathematicalFunction<Energy>(electrochemicalPotential[ion->getIonIndex()][1],
                    Mathematics::calculateAverage);

            Energy avgElectrochemicalPotential_region4
                = Mathematics::mathematicalFunction<Energy>(electrochemicalPotential[ion->getIonIndex()][3],
                    Mathematics::calculateAverage);

            for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
            {
                if (region == 1 || region == 3)
                {
                    temporaryFittingParameters.push_back(Mathematics::mathematicalFunction< Length, Energy,
                        std::map<std::string, long double> >(individualRegionData[region - 1]->rnemdAxis,
                            electrochemicalPotential[ion->getIonIndex()][region - 1],
                                Mathematics::linearLeastSquaresFitting));

                    temporaryStorageVector.push_back( Force(temporaryFittingParameters[region - 1]["slope"]) );
                }
                else
                {
                    temporaryFittingParameters.push_back(temporaryFittingParameters[region - 2]);

                    temporaryStorageVector.push_back(
                        (avgElectrochemicalPotential_region2 - avgElectrochemicalPotential_region4)
                            / rnemdParameters->inferred->slabWidth);
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
            outputFileStream << "# Fitting Parameters:\n";

            for (const auto& ion : rnemdParameters->ionicSpecies)
                outputFileStream << "#   " << ion->getIonName()
                                 << ": y = " << fittingParameters[ion->getIonIndex()][region - 1]["slope"]
                                 << "x + " << fittingParameters[ion->getIonIndex()][region - 1]["intercept"]
                                 << "\n";
        }
    }
}
