// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDAnalysisMethod.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:18:42
// Description: Template method interface for the ChargedRNEMD program

#ifndef ND_RESEARCH_OPENMD_CHARGEDRNEMDANALYSISMETHOD_HPP
#define ND_RESEARCH_OPENMD_CHARGEDRNEMDANALYSISMETHOD_HPP

#include <fstream>
#include <memory>
#include <string_view>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>

#include "chargedRNEMDFile.hpp"
#include "../../RNEMDFileParsing/include/rnemdRegion.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class ChargedRNEMDAnalysisMethod
    {
    private:
        struct InternalCalculations;
        std::unique_ptr<InternalCalculations> p_Impl;

        void calculateElectrochemicalPotential();
        void calculateTransportProperties();

        // Required Implementation
        virtual void calculateGradientOfElectrochemicalPotential() = 0;
        virtual void printAdditionalRegionHeader(std::ofstream& outputFileStream, int region) = 0;

    protected:
        ChargedRNEMDFilePtr rnemdFile;
        ChargedRNEMDParametersPtr rnemdParameters;
        std::vector<RNEMDDataPtr> individualRegionData;

        std::vector< std::vector< std::vector<PhysicalQuantities::Energy> > > electrochemicalPotential;
        std::vector <std::vector<PhysicalQuantities::Force> > gradientOfElectrochemicalPotential;
        std::vector< std::vector<PhysicalQuantities::ElectricConductivity> > sigma;
        std::vector< std::vector<PhysicalQuantities::MolarConductivity> > lambda;
        std::vector< std::vector<PhysicalQuantities::Mobility> > mobility;

        void calculateElectricPotential();

        // Optional Implementation
        virtual void preProcess() {};
        virtual void postProcess() {};

    public:
        explicit ChargedRNEMDAnalysisMethod(const ChargedRNEMDFilePtr& RNEMDFile);
        explicit ChargedRNEMDAnalysisMethod(std::string_view FullFileName);
        virtual ~ChargedRNEMDAnalysisMethod();

        void process();
        void printOutputToFile();
    };

    using ChargedRNEMDAnalysisMethodPtr = std::shared_ptr<ChargedRNEMDAnalysisMethod>;
}

#endif
