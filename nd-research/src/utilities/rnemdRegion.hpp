// Copyright (c) 2019-2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: rnemdRegion.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/08/2020-21:39:44
// Description: Functionality pertaining to splitting the RNEMD file into separate regions

#ifndef ND_RESEARCH_RNEMDREGION_HPP
#define ND_RESEARCH_RNEMDREGION_HPP

#include <memory>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>

#include "../fileTypes/rnemdFiles/rnemdFile.hpp"

namespace ND_Research
{
    class RNEMDRegion
    {
    private:
        RNEMDFile rnemdFile;

        int lowerIndexOfRegion, upperIndexOfRegion;
        int lowerIndexOfFirstRegion {}, upperIndexOfFirstRegion {};

        std::vector<PhysicalQuantities::Length> regionBounds;

        RNEMDDataPtr nonRegionSpecificData { std::make_shared<RNEMDData>() };
        RNEMDParametersPtr rnemdParameters { std::make_shared<RNEMDParameters>() };

        std::vector<RNEMDDataPtr> regionSpecificData;

        void parseWrappedZSelections();
        void setRNEMDRegionIndicies(int region);

        template<typename T>
        std::vector<T> regionSlicer(const std::vector<T>& PhysicalQuantity);

        PhysicalQuantities::Length convertWrappedZ_to_z(const PhysicalQuantities::Length& wrapped_z) const
        {
            return (rnemdParameters->inferred.boxSize / 2.0_) + wrapped_z;
        }

        int boundFinder(const PhysicalQuantities::Length& regionBound) const
        {
            return std::upper_bound(nonRegionSpecificData->rnemdAxis.begin(), nonRegionSpecificData->rnemdAxis.end(),
                (regionBound - nonRegionSpecificData->rnemdAxis[0])) - nonRegionSpecificData->rnemdAxis.begin();
        }

        void makeFirstRegionContinuous()
        {
            for (auto& z : regionSpecificData[0]->rnemdAxis)
                if (z > regionSpecificData[0]->rnemdAxis.back())
                    z -= rnemdParameters->inferred.boxSize;
        }

    public:
        RNEMDRegion(const RNEMDFile& RNEMDFile);

        std::vector<RNEMDDataPtr> getRegionSpecificData() const { return regionSpecificData; }
    };
}

#endif
