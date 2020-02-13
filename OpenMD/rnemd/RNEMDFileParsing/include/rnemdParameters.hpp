// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdParameters.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/20/2020-15:44:50
// Description: Defines data structures dedicated to holding the data from a given RNEMD file

#ifndef RNEMDPARAMETERS_HPP
#define RNEMDPARAMETERS_HPP

#include <array>
#include <memory>
#include <vector>
#include <string>
#include <utilities-api/physicalQuantities.hpp>

namespace OpenMD::RNEMD
{
    struct RNEMDBlockParameters
    {
        std::string exchangeMethod;
        std::string fluxType;

        std::string privilegedAxis;
        Utilities_API::PhysicalQuantities::Time exchangeTime;
        std::vector<std::string> objectSelection;
        std::array<Utilities_API::PhysicalQuantities::Length, 2> selectionA;
        std::array<Utilities_API::PhysicalQuantities::Length, 2> selectionB;
        std::vector<std::string> outputSelection;
    };

    using RNEMDBlockParametersPtr = std::shared_ptr<RNEMDBlockParameters>;


    struct RNEMDReportParameters
    {
        Utilities_API::PhysicalQuantities::Time runningTime;

        // Target flux
        Utilities_API::PhysicalQuantities::MolarEnergyFlux kineticFlux;
        std::array<Utilities_API::PhysicalQuantities::MomentumFlux, 3> momentumFlux;
        std::array<Utilities_API::PhysicalQuantities::MomentumFlux, 3> angularMomentumFlux;
        Utilities_API::PhysicalQuantities::CurrentDensity currentDensity;

        // Target one-time exchanges
        Utilities_API::PhysicalQuantities::MolarEnergy kineticTarget;
        std::array<Utilities_API::PhysicalQuantities::Momentum, 3> momentumTarget;
        std::array<Utilities_API::PhysicalQuantities::Momentum, 3> angularMomentumTarget;

        // Actual exchange totals
        Utilities_API::PhysicalQuantities::MolarEnergy kineticExchange;
        std::array<Utilities_API::PhysicalQuantities::Momentum, 3> momentumExchange;
        std::array<Utilities_API::PhysicalQuantities::Momentum, 3> angularMomentumExchange;

        // Actual flux
        Utilities_API::PhysicalQuantities::MolarEnergyFlux Jz;
        std::array<Utilities_API::PhysicalQuantities::MomentumFlux, 3> JzP;
        std::array<Utilities_API::PhysicalQuantities::MomentumFlux, 3> JzL;
        Utilities_API::PhysicalQuantities::CurrentDensity Jc_total;
        Utilities_API::PhysicalQuantities::CurrentDensity Jc_cation;
        Utilities_API::PhysicalQuantities::CurrentDensity Jc_anion;

        // Exchange statistics
        size_t trialCount;
        size_t failTrialCount;
        size_t failRootCount;
    };

    using RNEMDReportParametersPtr = std::shared_ptr<RNEMDReportParameters>;


    struct RNEMDInferredParameters
    {
        bool hasSelectionB {false};

        int dataFieldLabelIndex;
        int numberOfRegions;

        Utilities_API::PhysicalQuantities::Length slabWidth;
        Utilities_API::PhysicalQuantities::Length boxSize;
    };

    using RNEMDInferredParametersPtr = std::shared_ptr<RNEMDInferredParameters>;


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

        std::vector<Utilities_API::PhysicalQuantities::Length> rnemdAxis;
        std::vector<Utilities_API::PhysicalQuantities::Length> radius;
        std::vector<Utilities_API::PhysicalQuantities::Temperature> temperature;
        std::array<std::vector<Utilities_API::PhysicalQuantities::Velocity>, 3> velocity;
        std::array<std::vector<Utilities_API::PhysicalQuantities::Velocity>, 3> angularVelocity;
        std::vector<Utilities_API::PhysicalQuantities::MassDensity> density;
        std::vector< std::vector<Utilities_API::PhysicalQuantities::Concentration> > activity;
        std::array<std::vector<Utilities_API::PhysicalQuantities::ElectricField>, 3> electricField;
        std::vector<Utilities_API::PhysicalQuantities::ElectricPotential> electricPotential;
    };

    using RNEMDDataPtr =  std::shared_ptr<RNEMDData>;
}

#endif
