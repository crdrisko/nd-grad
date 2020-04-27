// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
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
    struct RNEMDBlockParameters
    {
        std::string exchangeMethod;
        std::string fluxType;

        std::string privilegedAxis;
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


    struct RNEMDParameters
    {
        RNEMDBlockParameters block;
        RNEMDReportParameters report;
        RNEMDInferredParameters inferred;
    };

    using RNEMDParametersPtr = std::shared_ptr<RNEMDParameters>;


    struct RNEMDData
    {
        static inline std::vector<std::string> dataLabels { "z(Angstroms)",
                                                            "R(Angstroms)",
                                                            "Temperature(K)",
                                                            "Velocity(angstroms/fs)",
                                                            "AngularVelocity(angstroms^2/fs)",
                                                            "Density(g cm^-3)",
                                                            "Activity(unitless)",
                                                            "Electric Field(kcal/mol/angstroms/e)",
                                                            "Electrostatic Potential(kcal/mol/e)" };

        std::vector<PhysicalQuantities::Length> rnemdAxis;
        std::vector<PhysicalQuantities::Length> radius;
        std::vector<PhysicalQuantities::Temperature> temperature;
        std::array<std::vector<PhysicalQuantities::Velocity>, 3> velocity;
        std::array<std::vector<PhysicalQuantities::Velocity>, 3> angularVelocity;
        std::vector<PhysicalQuantities::MassDensity> density;
        std::vector< std::vector<PhysicalQuantities::Concentration> > activity;
        std::array<std::vector<PhysicalQuantities::ElectricField>, 3> electricField;
        std::vector<PhysicalQuantities::ElectricPotential> electricPotential;
    };

    using RNEMDDataPtr = std::shared_ptr<RNEMDData>;
}

#endif
