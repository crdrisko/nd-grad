// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDParameters.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/05/2020-12:55:06
// Description: Defines data structures dedicated to holding the data from a given charged-RNEMD file

#ifndef CHARGEDRNEMDPARAMETERS_HPP
#define CHARGEDRNEMDPARAMETERS_HPP

#include <utilities-api/errors.hpp>
#include "../../RNEMDFileParsing/include/rnemdParameters.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class IonicSpecies
    {
    private:
        int ionIndex {};
        std::string ionName;
        Utilities_API::PhysicalQuantities::ElectricCharge ionCharge;

        static inline std::map<std::string_view, int> magnitudeOfIonicCharge { {"Na+",  1},
                                                                               {"Li+",  1},
                                                                               {"Ca+2", 2},
                                                                               {"Cl-",  1} };

        Utilities_API::PhysicalQuantities::ElectricCharge getChargeOfIon(std::string_view ionName)
        {
            Utilities_API::PhysicalQuantities::ElectricCharge charge(magnitudeOfIonicCharge[ionName]);

            if (magnitudeOfIonicCharge.count(ionName) != 1)
                Utilities_API::Errors::printFatalErrorMessage(1,
                    "Only Cl-, Na+, Li+, and Ca+2 are currently supported.");

            return (ionName == "Cl-") ? charge.negateQuantity() : charge;
        }

    public:
        IonicSpecies(std::string_view IonName, int IonIndex = 0) : ionName{IonName}, ionIndex{IonIndex}
        {
            ionCharge = this->getChargeOfIon(ionName);
        }

        int getIonIndex() const { return this->ionIndex; }
        std::string getIonName() const { return this->ionName; }
        Utilities_API::PhysicalQuantities::ElectricCharge getIonCharge() const { return this->ionCharge; }
    };

    using IonicSpeciesPtr = std::shared_ptr<IonicSpecies>;


    struct ChargedRNEMDParameters
    {
        IonicSpeciesPtr anion, cation;
        RNEMDBlockParametersPtr block;
        RNEMDReportParametersPtr report;
        RNEMDInferredParametersPtr inferred;
    };

    using ChargedRNEMDParametersPtr = std::shared_ptr<ChargedRNEMDParameters>;
}

#endif
