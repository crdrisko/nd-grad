// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: rnemdRegion.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/08/2020-21:39:44
// Description: Functionality pertaining to splitting the RNEMD file into separate regions

#ifndef ND_RESEARCH_OPENMD_RNEMDREGION_HPP
#define ND_RESEARCH_OPENMD_RNEMDREGION_HPP

#include <memory>
#include <vector>

#include "rnemdFile.hpp"

namespace OpenMD::RNEMD
{
    class RNEMDRegion
    {
    private:
        class RNEMDRegionImpl;
        RNEMDFilePtr rnemdFile;
        std::unique_ptr<RNEMDRegionImpl> p_Impl;

    public:
        RNEMDRegion(const RNEMDFilePtr& RNEMDFile);
        ~RNEMDRegion();

        std::vector<RNEMDDataPtr> getRegionSpecificData() const;
    };

    using RNEMDRegionPtr = std::shared_ptr<RNEMDRegion>;
}

#endif
