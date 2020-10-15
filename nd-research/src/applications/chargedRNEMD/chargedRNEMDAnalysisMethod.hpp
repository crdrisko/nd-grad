// Copyright (c) 2019-2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
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

        // Required implementation for a given analysis method
        virtual void calculateGradientOfElectrochemicalPotential() = 0;
        virtual void printAdditionalRegionHeader(std::ofstream& outputFileStream, int region) = 0;

    protected:
        ChargedRNEMDFilePtr rnemdFile;
        ChargedRNEMDParametersPtr rnemdParameters;
        std::vector<RNEMDDataPtr> individualRegionData;

        std::vector<std::vector<std::vector<PhysicalQuantities::Energy>>> electrochemicalPotential;

        // Use arrays of physical quantities to propagate error through our transport property calculations
        std::vector<std::vector<std::array<PhysicalQuantities::Force, 2>>> gradientOfElectrochemicalPotential;
        std::vector<std::vector<std::array<PhysicalQuantities::ElectricConductivity, 2>>> sigma;
        std::vector<std::vector<std::array<PhysicalQuantities::MolarConductivity, 2>>> lambda;
        std::vector<std::vector<std::array<PhysicalQuantities::Mobility, 2>>> mobility;

        void calculateElectricPotential();

        // Optional implementation for a given analysis method
        virtual void preProcess() {};
        virtual void postProcess() {};

    public:
        explicit ChargedRNEMDAnalysisMethod(const ChargedRNEMDFilePtr& RNEMDFile);
        explicit ChargedRNEMDAnalysisMethod(std::string_view FullFileName);
        virtual ~ChargedRNEMDAnalysisMethod();

        void process();
        void printOutputToFile();
        void printOptimizationAnalysisToFile(std::string outputFileName = "");
    };

    using ChargedRNEMDAnalysisMethodPtr = std::shared_ptr<ChargedRNEMDAnalysisMethod>;
}

#endif
