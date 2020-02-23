// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: regionFitting.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:43:08
// Description: Implementation of the pure virtual functions defined in the chargedRNEMDAnalysisMethod class

#include "../include/regionFitting.hpp"

using std::vector;
using namespace Utilities_API::PhysicalQuantities;

namespace OpenMD::RNEMD::ChargedRNEMD
{
    void RegionFitting::calculateGradientOfElectrochemicalPotential()
    {
        for (const auto& ion : rnemdParameters->ionicSpecies)
        {
            std::vector<Force> temporaryStorageVector;
            std::vector< std::map<std::string, long double> > temporaryFittingParameters;

            for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
            {
                temporaryFittingParameters.push_back(Mathematics::mathematicalFunction< std::map<std::string,
                    long double> >(individualRegionData[region - 1]->rnemdAxis,
                        electrochemicalPotential[ion->getIonIndex()][region - 1],
                            Mathematics::linearLeastSquaresFitting));

                temporaryStorageVector.push_back( Force(temporaryFittingParameters[region - 1]["slope"]) );
            }

            gradientOfElectrochemicalPotential.push_back(temporaryStorageVector);
            fittingParameters.push_back(temporaryFittingParameters);
        }
    }


    void RegionFitting::printAdditionalRegionHeader(std::ofstream& outputFileStream, int region)
    {
        outputFileStream << "# Fitting Parameters:\n";

        for (const auto& ion : rnemdParameters->ionicSpecies)
            outputFileStream << "#   " << ion->getIonName()
                             << ": y = " << fittingParameters[ion->getIonIndex()][region - 1]["slope"]
                             << "x + " << fittingParameters[ion->getIonIndex()][region - 1]["intercept"]
                             << "\n";
    }
}
