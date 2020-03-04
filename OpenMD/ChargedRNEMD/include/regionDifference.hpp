// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: regionDifference.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:19:58
// Description: A chargedRNEMD method which calculates the difference between two electrochemical potentials

#ifndef REGIONDIFFERENCE_HPP
#define REGIONDIFFERENCE_HPP

#include "chargedRNEMDAnalysisMethod.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class RegionDifference : public ChargedRNEMDAnalysisMethod
    {
    private:
        std::vector< std::vector< std::map<std::string, long double> > > fittingParameters;

        virtual void calculateGradientOfElectrochemicalPotential() override;
        virtual void printAdditionalRegionHeader(std::ofstream& outputFileStream, int region) override;

        virtual void preProcess() override { calculateElectricPotential(); }

    public:
        explicit RegionDifference(const ChargedRNEMDFilePtr& rnemdFile)
            : ChargedRNEMDAnalysisMethod{rnemdFile} {}
    };
}

#endif
