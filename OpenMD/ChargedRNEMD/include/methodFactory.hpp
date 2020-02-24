// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: methodFactory.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/20/2020-13:35:11
// Description: A factory class designed to generate the appropriate analysis method depending on the fluxType

#ifndef METHODFACTORY_HPP
#define METHODFACTORY_HPP

#include "regionFitting.hpp"
#include "regionDifference.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class MethodFactory
    {
    private:
        ChargedRNEMDFilePtr rnemdFile;

    public:
        explicit MethodFactory(const Utilities_API::Files::FileNamePtr& FileName)
            : rnemdFile{ std::make_shared<ChargedRNEMDFile>(FileName->getFullFileName()) } {}

        ChargedRNEMDAnalysisMethodPtr createMethod() const
        {
            const std::string fluxType {rnemdFile->getChargedRNEMDParameters()->block->fluxType};

            if (fluxType == "Single")
                return std::make_shared<RegionFitting>(this->rnemdFile);
            else
                return std::make_shared<RegionDifference>(this->rnemdFile);
        }
    };
}

#endif
