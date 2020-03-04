// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDAnalysisMethod.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:18:42
// Description: Template method interface for the chargedRNEMD program

#ifndef CHARGEDRNEMDANALYSISMETHOD_HPP
#define CHARGEDRNEMDANALYSISMETHOD_HPP

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

        std::vector< std::vector< std::vector<Utilities_API::PhysicalQuantities::Energy> > > electrochemicalPotential;
        std::vector <std::vector<Utilities_API::PhysicalQuantities::Force> > gradientOfElectrochemicalPotential;
        std::vector< std::vector<Utilities_API::PhysicalQuantities::ElectricConductivity> > sigma;
        std::vector< std::vector<Utilities_API::PhysicalQuantities::MolarConductivity> > lambda;
        std::vector< std::vector<Utilities_API::PhysicalQuantities::Mobility> > mobility;

        void calculateElectricPotential(const size_t& referencePoint = 0);

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
