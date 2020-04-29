// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdRegion.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/22/2020-15:21:57
// Description: Defines the functionality pertaining to splitting the RNEMD file into separate regions

#include <algorithm>
#include <memory>
#include <vector>

#include "rnemdRegion.hpp"

using namespace PhysicalQuantities;
using namespace PhysicalQuantities::Literals;

namespace ND_Research::RNEMDRegionSplitting
{
    RNEMDRegion::RNEMDRegion(const RNEMDFile& RNEMDFile) : rnemdFile{RNEMDFile}
    {
        rnemdParameters = rnemdFile.getRNEMDParameters();
        nonRegionSpecificData = rnemdFile.getAllDataFromFile();

        parseWrappedZSelections();

        for (int region {1}; region <= rnemdParameters->inferred.numberOfRegions; ++region)
        {
            setRNEMDRegionIndicies(region);

            regionSpecificData.push_back( std::make_shared<RNEMDData>() );

            regionSpecificData[region - 1]->rnemdAxis = regionSlicer(nonRegionSpecificData->rnemdAxis);
            regionSpecificData[region - 1]->radius = regionSlicer(nonRegionSpecificData->radius);
            regionSpecificData[region - 1]->temperature = regionSlicer(nonRegionSpecificData->temperature);
            regionSpecificData[region - 1]->density = regionSlicer(nonRegionSpecificData->density);
            regionSpecificData[region - 1]->electricPotential = regionSlicer(nonRegionSpecificData->electricPotential);

            // Split all axis directions for velocity, angularVelocity and electric field seperately
            for (int i {}; i < 3; ++i)
            {
                regionSpecificData[region - 1]->velocity[i] = regionSlicer(nonRegionSpecificData->velocity[i]);
                regionSpecificData[region - 1]->angularVelocity[i] = regionSlicer(nonRegionSpecificData->angularVelocity[i]);
                regionSpecificData[region - 1]->electricField[i] = regionSlicer(nonRegionSpecificData->electricField[i]);
            }

            // Split all species for activity seperately
            for (size_t i {}; i < nonRegionSpecificData->activity.size(); ++i)
                regionSpecificData[region - 1]->activity.push_back(regionSlicer(nonRegionSpecificData->activity[i]));
        }

        makeFirstRegionContinuous();
    }


    void RNEMDRegion::parseWrappedZSelections()
    {
        regionBounds.push_back(0.0_Ang);

        if (rnemdParameters->inferred.hasSelectionB)
            regionBounds.push_back(convertWrappedZ_to_z(rnemdParameters->block.selectionB[1]));

        regionBounds.push_back(convertWrappedZ_to_z(rnemdParameters->block.selectionA[0]));
        regionBounds.push_back(convertWrappedZ_to_z(rnemdParameters->block.selectionA[1]));

        if (rnemdParameters->inferred.hasSelectionB)
            regionBounds.push_back(convertWrappedZ_to_z(rnemdParameters->block.selectionB[0]));

        regionBounds.push_back(rnemdParameters->inferred.boxSize);
    }


    void RNEMDRegion::setRNEMDRegionIndicies(int region)
    {
        lowerIndexOfRegion = boundFinder(regionBounds[region - 1]);
        upperIndexOfRegion = boundFinder(regionBounds[region]);
        lowerIndexOfFirstRegion = 0;
        upperIndexOfFirstRegion = 0;

        if (region == 1)
        {
            lowerIndexOfFirstRegion = lowerIndexOfRegion;
            upperIndexOfFirstRegion = upperIndexOfRegion;

            lowerIndexOfRegion = boundFinder(regionBounds[rnemdParameters->inferred.numberOfRegions]);
            upperIndexOfRegion = boundFinder(regionBounds[rnemdParameters->inferred.numberOfRegions + 1]);
        }
    }


    template<typename T>
    std::vector<T> RNEMDRegion::regionSlicer(const std::vector<T>& PhysicalQuantity)
    {
        if ( PhysicalQuantity.empty() )
            return PhysicalQuantity;

        std::vector<T> splitPhysicalQuantity;

        for (int i {lowerIndexOfRegion}; i < upperIndexOfRegion; ++i)
            splitPhysicalQuantity.push_back(PhysicalQuantity[i]);

        // Append first region on back of the last, defaults to off
        if ( (lowerIndexOfFirstRegion != 0) || (upperIndexOfFirstRegion != 0) )
        {
            int copyLowerIndexOfRegion {lowerIndexOfRegion};
            int copyUpperIndexOfRegion {upperIndexOfRegion};

            // Switch the indicies before recursive call so we don't retrigger this condition
            lowerIndexOfRegion = lowerIndexOfFirstRegion;
            upperIndexOfRegion = upperIndexOfFirstRegion;
            lowerIndexOfFirstRegion = 0;
            upperIndexOfFirstRegion = 0;

            std::vector<T> temporaryStorageVector { regionSlicer(PhysicalQuantity) };

            for (const auto& quantity : temporaryStorageVector)
                splitPhysicalQuantity.push_back(quantity);

            // Reset the index values so the other physical quantities can use the same
            lowerIndexOfFirstRegion = lowerIndexOfRegion;
            upperIndexOfFirstRegion = upperIndexOfRegion;
            lowerIndexOfRegion = copyLowerIndexOfRegion;
            upperIndexOfRegion = copyUpperIndexOfRegion;
        }

        return splitPhysicalQuantity;
    }
}
