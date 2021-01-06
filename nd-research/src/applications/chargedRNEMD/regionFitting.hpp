// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: regionFitting.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:20:07
// Description: A chargedRNEMD method which performs a linear fit on the electrochemical potential curves

#ifndef ND_RESEARCH_OPENMD_REGIONFITTING_HPP
#define ND_RESEARCH_OPENMD_REGIONFITTING_HPP

#include <fstream>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>

#include "chargedRNEMDAnalysisMethod.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class RegionFitting : public ChargedRNEMDAnalysisMethod
    {
    private:
        std::vector<std::vector<std::vector<PhysicalQuantities::Force>>> fittingParameters;

        virtual void calculateGradientOfElectrochemicalPotential() override;
        virtual void printAdditionalRegionHeader(std::ofstream& outputFileStream, int region) override;

        virtual void preProcess() override { calculateElectricPotential(); }

    public:
        explicit RegionFitting(const ChargedRNEMDFilePtr& rnemdFile)
            : ChargedRNEMDAnalysisMethod{rnemdFile} {}
    };
}

#endif
