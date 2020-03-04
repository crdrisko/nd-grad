// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: regionFitting.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:20:07
// Description: A chargedRNEMD method which performs a linear fit on the electrochemical potential curves

#ifndef REGIONFITTING_HPP
#define REGIONFITTING_HPP

#include "chargedRNEMDAnalysisMethod.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class RegionFitting : public ChargedRNEMDAnalysisMethod
    {
    private:
        std::vector< std::vector< std::map<std::string, long double> > > fittingParameters;

        virtual void calculateGradientOfElectrochemicalPotential() override;
        virtual void printAdditionalRegionHeader(std::ofstream& outputFileStream, int region) override;

        virtual void preProcess() override { calculateElectricPotential(); }

    public:
        explicit RegionFitting(const ChargedRNEMDFilePtr& rnemdFile)
            : ChargedRNEMDAnalysisMethod{rnemdFile} {}
    };
}

#endif
