// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: chargedRNEMDParameters.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/05/2020-12:55:06
// Description: Defines data structures dedicated to holding the data from a given charged-RNEMD file

#ifndef ND_RESEARCH_OPENMD_CHARGEDRNEMDPARAMETERS_HPP
#define ND_RESEARCH_OPENMD_CHARGEDRNEMDPARAMETERS_HPP

#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/errors.hpp>

#include "../../RNEMDFileParsing/include/rnemdParameters.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class IonicSpecies
    {
    private:
        std::string ionName;
        int ionIndex;
        PhysicalQuantities::ElectricCharge ionCharge;

        Utilities_API::Errors::ErrorMessagePtr errorMessage
            = std::make_shared<Utilities_API::Errors::FatalErrorMessage>("ChargedRNEMD", 1);

        static inline std::map<std::string_view, int> chargeOfCommonIons { {"Na+",   1},
                                                                           {"Li+",   1},
                                                                           {"Ca+2",  2},
                                                                           {"Cl-",  -1} };

        PhysicalQuantities::ElectricCharge getChargeOfIon(std::string_view ionName)
        {
            if (chargeOfCommonIons.count(ionName) != 1)
                errorMessage->printErrorMessage("Only Cl-, Na+, Li+, and Ca+2 are currently supported.");

            PhysicalQuantities::ElectricCharge charge(chargeOfCommonIons[ionName]);

            return charge;
        }

    public:
        IonicSpecies(std::string_view IonName, int IonIndex = 0) : ionName{IonName}, ionIndex{IonIndex}
        {
            ionCharge = getChargeOfIon(ionName);
        }

        int getIonIndex() const { return ionIndex; }
        std::string getIonName() const { return ionName; }
        PhysicalQuantities::ElectricCharge getIonCharge() const { return ionCharge; }
    };

    using IonicSpeciesPtr = std::shared_ptr<IonicSpecies>;


    struct ChargedRNEMDParameters
    {
        RNEMDBlockParametersPtr block;
        RNEMDReportParametersPtr report;
        RNEMDInferredParametersPtr inferred;
        std::vector<IonicSpeciesPtr> ionicSpecies;
    };

    using ChargedRNEMDParametersPtr = std::shared_ptr<ChargedRNEMDParameters>;
}

#endif
