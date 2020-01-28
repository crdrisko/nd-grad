// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdRegion.cpp - Version 1.0.1
// Author: cdrisko
// Date: 01/22/2020-15:21:57
// Description: Defines the functionality pertaining to splitting the RNEMD file into separate regions

#include "include/rnemdRegion.hpp"

namespace OpenMD::RNEMD
{
    RNEMDRegion::RNEMDRegion(const RNEMDDataPtr& NonRegionSpecificData, int lowerIndexOfRegion,
        int upperIndexOfRegion, int lowerIndexOfFirstRegion, int upperIndexOfFirstRegion)
    {
        nonRegionSpecificData = NonRegionSpecificData;

        if ( !nonRegionSpecificData->rnemdAxis.empty() )
            regionSpecificData->rnemdAxis = regionSlicer(nonRegionSpecificData->rnemdAxis,
                lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion);

        if ( !nonRegionSpecificData->radius.empty() )
            regionSpecificData->radius = regionSlicer(nonRegionSpecificData->radius,
                lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion);

        if ( !nonRegionSpecificData->temperature.empty() )
            regionSpecificData->temperature = regionSlicer(nonRegionSpecificData->temperature,
                lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion);

        if ( !nonRegionSpecificData->density.empty() )
            regionSpecificData->density = regionSlicer(nonRegionSpecificData->density,
                lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion );

        if ( !nonRegionSpecificData->electricPotential.empty() )
            regionSpecificData->electricPotential = regionSlicer(nonRegionSpecificData->electricPotential,
                lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion );

        // Split all axis directions for velocity, angularVelocity and electric field seperately
        for (int i {}; i < 3; ++i)
        {
            if ( !nonRegionSpecificData->velocity[i].empty() )
                regionSpecificData->velocity[i] = regionSlicer(nonRegionSpecificData->velocity[i],
                    lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion);

            if ( !nonRegionSpecificData->angularVelocity[i].empty() )
                regionSpecificData->angularVelocity[i] = regionSlicer(nonRegionSpecificData->angularVelocity[i],
                    lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion);

            if ( !nonRegionSpecificData->electricField[i].empty() )
                regionSpecificData->electricField[i] = regionSlicer(nonRegionSpecificData->electricField[i],
                    lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion);
        }

        // Split all species for concentration seperately
        for (int i {}; i < nonRegionSpecificData->activity.size(); ++i)
            if ( !nonRegionSpecificData->activity[i].empty() )
                regionSpecificData->activity.push_back(regionSlicer(nonRegionSpecificData->activity[i],
                    lowerIndexOfRegion, upperIndexOfRegion, lowerIndexOfFirstRegion, upperIndexOfFirstRegion));
    }


    template<typename T>
    std::vector<T> RNEMDRegion::regionSlicer(std::vector<T> PhysicalQuantity, int lowerIndexOfRegion,
        int upperIndexOfRegion, int lowerIndexOfFirstRegion, int upperIndexOfFirstRegion)
    {
        std::vector<T> splitPhysicalQuantity;

        for (int i {lowerIndexOfRegion}; i < upperIndexOfRegion; ++i)
            splitPhysicalQuantity.push_back(PhysicalQuantity[i]);

        // Append first region on back of the last, defaults to off
        if ( (lowerIndexOfFirstRegion != 0) || (upperIndexOfFirstRegion != 0) )
        {
            std::vector<T> temporaryStorageVector { regionSlicer(PhysicalQuantity,
                lowerIndexOfFirstRegion, upperIndexOfFirstRegion) };

            for (const auto& quantity : temporaryStorageVector)
                splitPhysicalQuantity.push_back(quantity);
        }

        return splitPhysicalQuantity;
    }
}
