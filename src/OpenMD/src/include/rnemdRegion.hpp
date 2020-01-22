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
        RNEMDDataPtr regionSpecificData { std::make_shared<RNEMDData>() };
        static inline RNEMDDataPtr nonRegionSpecificData { std::make_shared<RNEMDData>() };

        template<typename T>
        std::vector<T> regionSlicer(std::vector<T> PhysicalQuantity, int lowerIndexOfRegion,
            int upperIndexOfRegion, int lowerIndexOfFirstRegion = 0, int upperIndexOfFirstRegion = 0);

    public:
        RNEMDRegion(const RNEMDDataPtr& NonRegionSpecificData, int lowerIndexOfRegion,
            int upperIndexOfRegion, int lowerIndexOfFirstRegion = 0, int upperIndexOfFirstRegion = 0);

        RNEMDDataPtr getRegionSpecificData() const { return regionSpecificData; }
    };

    using RNEMDRegionPtr = std::shared_ptr<RNEMDRegion>;
}

#endif
