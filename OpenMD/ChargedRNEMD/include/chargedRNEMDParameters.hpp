// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDParameters.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/05/2020-12:55:06
// Description: Defines data structures dedicated to holding the data from a given charged-RNEMD file

#ifndef CHARGEDRNEMDPARAMETERS_HPP
#define CHARGEDRNEMDPARAMETERS_HPP

#include <utils-api/errors.hpp>
#include "../../RNEMDFileParsing/include/rnemdParameters.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class IonicSpecies
    {
    private:
        std::string ionName;
        int ionIndex;
        Utilities_API::PhysicalQuantities::ElectricCharge ionCharge;

        static inline std::map<std::string_view, int> magnitudeOfIonicCharge { {"Na+",  1},
                                                                               {"Li+",  1},
                                                                               {"Ca+2", 2},
                                                                               {"Cl-",  1} };

        Utilities_API::PhysicalQuantities::ElectricCharge getChargeOfIon(std::string_view ionName)
        {
            if (magnitudeOfIonicCharge.count(ionName) != 1)
                Utilities_API::Errors::printFatalErrorMessage(1,
                    "Only Cl-, Na+, Li+, and Ca+2 are currently supported");

            Utilities_API::PhysicalQuantities::ElectricCharge charge(magnitudeOfIonicCharge[ionName]);

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


    // template <typename T>
    // struct TransportProperty
    // {
    //     std::vector< std::vector<T> > magnitude;
    //     std::vector< std::vector<T> > standardDeviation;
    // };


    struct ChargedRNEMDParameters
    {
        RNEMDBlockParametersPtr block;
        RNEMDReportParametersPtr report;
        RNEMDInferredParametersPtr inferred;
        std::vector<IonicSpeciesPtr> ionicSpecies;

        // TransportProperty<Utilities_API::PhysicalQuantities::ElectricConductivity> sigma;
        // TransportProperty<Utilities_API::PhysicalQuantities::MolarConductivity> lambda;
        // TransportProperty<Utilities_API::PhysicalQuantities::Mobility> mobility;
    };

    using ChargedRNEMDParametersPtr = std::shared_ptr<ChargedRNEMDParameters>;
}

#endif
