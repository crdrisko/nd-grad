// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for more information.
//
// Name: rnemdParameters.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/20/2020-15:44:50
// Description: Defines a few structures dedicated to holding the parameters associated with an .rnemd file

#ifndef ND_RESEARCH_RNEMDPARAMETERS_HPP
#define ND_RESEARCH_RNEMDPARAMETERS_HPP

#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/containers.hpp>

namespace ND_Research
{
    struct RNEMDParameters
    {
        struct RNEMDBlockParameters
        {
            std::string exchangeMethod;
            std::string fluxType;

            char privilegedAxis;
            PhysicalQuantities::Time exchangeTime;
            std::vector<std::string> objectSelection;
            std::array<PhysicalQuantities::Length, 2> selectionA;
            std::array<PhysicalQuantities::Length, 2> selectionB;
            std::vector<std::string> outputSelection;
        };

        struct RNEMDReportParameters
        {
            PhysicalQuantities::Time runningTime;

            // Target fluxes
            PhysicalQuantities::MolarEnergyFlux kineticFlux;
            Utilities_API::Containers::Vector3D<PhysicalQuantities::MomentumFlux> momentumFlux;
            Utilities_API::Containers::Vector3D<PhysicalQuantities::MomentumFlux> angularMomentumFlux;
            PhysicalQuantities::CurrentDensity currentDensity;

            // Target one-time exchanges
            PhysicalQuantities::MolarEnergy kineticTarget;
            Utilities_API::Containers::Vector3D<PhysicalQuantities::Momentum> momentumTarget;
            Utilities_API::Containers::Vector3D<PhysicalQuantities::Momentum> angularMomentumTarget;

            // Actual exchange totals
            PhysicalQuantities::MolarEnergy kineticExchange;

            Utilities_API::Containers::Vector3D<PhysicalQuantities::Momentum> momentumExchange;
            Utilities_API::Containers::Vector3D<PhysicalQuantities::Momentum> angularMomentumExchange;

            // Actual fluxes
            PhysicalQuantities::MolarEnergyFlux Jz;
            Utilities_API::Containers::Vector3D<PhysicalQuantities::MomentumFlux> JzP;
            Utilities_API::Containers::Vector3D<PhysicalQuantities::MomentumFlux> JzL;
            PhysicalQuantities::CurrentDensity Jc_total;
            PhysicalQuantities::CurrentDensity Jc_cation;
            PhysicalQuantities::CurrentDensity Jc_anion;

            // Exchange statistics
            std::size_t trialCount {};
            std::size_t failTrialCount {};
            std::size_t failRootCount {};
        };

        struct RNEMDInferredParameters
        {
            bool hasSelectionB {false};

            int dataFieldLabelIndex {};
            int numberOfRegions {};

            PhysicalQuantities::Length slabWidth;
            PhysicalQuantities::Length boxSize;

            double percentageOfKicksFailed {};
        };

        RNEMDBlockParameters block;
        RNEMDReportParameters report;
        RNEMDInferredParameters inferred;
    };

    using RNEMDParametersPtr = std::shared_ptr<RNEMDParameters>;


    struct RNEMDData
    {
        std::vector<PhysicalQuantities::Length> rnemdAxis;
        std::vector<PhysicalQuantities::Temperature> temperature;
        Utilities_API::Containers::Vector3D<std::vector<PhysicalQuantities::Velocity>> velocity;
        Utilities_API::Containers::Vector3D<std::vector<PhysicalQuantities::AngularVelocity>> angularVelocity;
        std::vector<PhysicalQuantities::MassDensity> density;
        std::vector<std::vector<PhysicalQuantities::Concentration>> activity;
        Utilities_API::Containers::Vector3D<std::vector<PhysicalQuantities::ElectricField>> electricField;
        std::vector<PhysicalQuantities::ElectricPotential> electricPotential;
    };

    using RNEMDDataPtr = std::shared_ptr<RNEMDData>;
}

#endif
