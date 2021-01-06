// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: methodFactory.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/20/2020-13:35:11
// Description: A factory class designed to generate the appropriate analysis method depending on the fluxType

#ifndef ND_RESEARCH_OPENMD_METHODFACTORY_HPP
#define ND_RESEARCH_OPENMD_METHODFACTORY_HPP

#include <memory>
#include <string>
#include <string_view>

#include "regionFitting.hpp"
#include "regionDifference.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class MethodFactory
    {
    private:
        ChargedRNEMDFilePtr rnemdFile;

    public:
        explicit MethodFactory(std::string_view FileName)
            : rnemdFile{ std::make_shared<ChargedRNEMDFile>(FileName) } {}

        ChargedRNEMDAnalysisMethodPtr createMethod() const
        {
            const std::string fluxType { rnemdFile->getChargedRNEMDParameters()->block->fluxType };

            if (fluxType == "Single")
                return std::make_shared<RegionFitting>(rnemdFile);
            else
                return std::make_shared<RegionDifference>(rnemdFile);
        }
    };
}

#endif
