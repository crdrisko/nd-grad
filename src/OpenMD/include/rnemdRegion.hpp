// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: rnemdRegion.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/08/2020-21:39:44
// Description: Functionality pertaining to splitting the RNEMD file into separate regions

#ifndef RNEMDREGION_HPP
#define RNEMDREGION_HPP

#include "rnemdParameters.hpp"

namespace OpenMD::RNEMD
{
    class RNEMDRegion
    {
    private:
        int lowerIndexOfRegion, upperIndexOfRegion;
        int lowerIndexOfFirstRegion {}, upperIndexOfFirstRegion {};

        RNEMDDataPtr regionSpecificData { std::make_shared<RNEMDData>() };
        static inline RNEMDDataPtr nonRegionSpecificData { std::make_shared<RNEMDData>() };

        template<typename T>
        std::vector<T> regionSlicer(std::vector<T> PhysicalQuantity);

    public:
        RNEMDRegion(const RNEMDDataPtr& NonRegionSpecificData, int LowerIndexOfRegion,
            int UpperIndexOfRegion, int LowerIndexOfFirstRegion = 0, int UpperIndexOfFirstRegion = 0);

        RNEMDDataPtr getRegionSpecificData() const { return regionSpecificData; }

        void makeFirstRegionContinuous(Utilities_API::PhysicalQuantities::Length boxSize)
        {
            for (auto& z : regionSpecificData->rnemdAxis)
                if (z > regionSpecificData->rnemdAxis.back())
                    z -= boxSize;
        }
    };

    using RNEMDRegionPtr = std::shared_ptr<RNEMDRegion>;
}

#endif
