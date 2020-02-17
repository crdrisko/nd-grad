// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdRegion.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/22/2020-15:21:57
// Description: Defines the functionality pertaining to splitting the RNEMD file into separate regions

#include "../include/rnemdRegion.hpp"

namespace OpenMD::RNEMD
{
    RNEMDRegion::RNEMDRegion(const RNEMDDataPtr& NonRegionSpecificData, int LowerIndexOfRegion,
        int UpperIndexOfRegion, int LowerIndexOfFirstRegion, int UpperIndexOfFirstRegion)
        : lowerIndexOfRegion{LowerIndexOfRegion}, upperIndexOfRegion{UpperIndexOfRegion},
          lowerIndexOfFirstRegion{LowerIndexOfFirstRegion}, upperIndexOfFirstRegion{UpperIndexOfFirstRegion}
    {
        nonRegionSpecificData = NonRegionSpecificData;

        regionSpecificData->rnemdAxis = regionSlicer(nonRegionSpecificData->rnemdAxis);
        regionSpecificData->radius = regionSlicer(nonRegionSpecificData->radius);
        regionSpecificData->temperature = regionSlicer(nonRegionSpecificData->temperature);
        regionSpecificData->density = regionSlicer(nonRegionSpecificData->density);
        regionSpecificData->electricPotential = regionSlicer(nonRegionSpecificData->electricPotential);

        // Split all axis directions for velocity, angularVelocity and electric field seperately
        for (int i {}; i < 3; ++i)
        {
            regionSpecificData->velocity[i] = regionSlicer(nonRegionSpecificData->velocity[i]);
            regionSpecificData->angularVelocity[i] = regionSlicer(nonRegionSpecificData->angularVelocity[i]);
            regionSpecificData->electricField[i] = regionSlicer(nonRegionSpecificData->electricField[i]);
        }

        // Split all species for concentration seperately
        for (size_t i {}; i < nonRegionSpecificData->activity.size(); ++i)
            regionSpecificData->activity.push_back(regionSlicer(nonRegionSpecificData->activity[i]));
    }

    template<typename T>
    std::vector<T> RNEMDRegion::regionSlicer(std::vector<T> PhysicalQuantity)
    {
        if ( PhysicalQuantity.empty() )
            return PhysicalQuantity;

        std::vector<T> splitPhysicalQuantity;

        for (int i {lowerIndexOfRegion}; i < upperIndexOfRegion; ++i)
            splitPhysicalQuantity.push_back(PhysicalQuantity[i]);

        // Append first region on back of the last, defaults to off
        if ( (lowerIndexOfFirstRegion != 0) || (upperIndexOfFirstRegion != 0) )
        {
            RNEMDRegionPtr firstRegion { std::make_shared<RNEMDRegion>(nonRegionSpecificData,
                lowerIndexOfFirstRegion, upperIndexOfFirstRegion) };

            std::vector<T> temporaryStorageVector { firstRegion->regionSlicer(PhysicalQuantity) };

            for (const auto& quantity : temporaryStorageVector)
                splitPhysicalQuantity.push_back(quantity);
        }

        return splitPhysicalQuantity;
    }
}
