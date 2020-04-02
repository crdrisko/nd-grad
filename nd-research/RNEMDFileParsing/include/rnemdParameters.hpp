// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdParameters.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/20/2020-15:44:50
// Description: Defines data structures dedicated to holding the data from a given RNEMD file

#ifndef ND_RESEARCH_OPENMD_RNEMDPARAMETERS_HPP
#define ND_RESEARCH_OPENMD_RNEMDPARAMETERS_HPP

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>

namespace OpenMD::RNEMD
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

    using RNEMDBlockParametersPtr = std::shared_ptr<RNEMDBlockParameters>;


    struct RNEMDReportParameters
    {
        PhysicalQuantities::Time runningTime;

        // Target flux
        PhysicalQuantities::MolarEnergyFlux kineticFlux;
        std::array<PhysicalQuantities::MomentumFlux, 3> momentumFlux;
        std::array<PhysicalQuantities::MomentumFlux, 3> angularMomentumFlux;
        PhysicalQuantities::CurrentDensity currentDensity;

        // Target one-time exchanges
        PhysicalQuantities::MolarEnergy kineticTarget;
        std::array<PhysicalQuantities::Momentum, 3> momentumTarget;
        std::array<PhysicalQuantities::Momentum, 3> angularMomentumTarget;

        // Actual exchange totals
        PhysicalQuantities::MolarEnergy kineticExchange;
        std::array<PhysicalQuantities::Momentum, 3> momentumExchange;
        std::array<PhysicalQuantities::Momentum, 3> angularMomentumExchange;

        // Actual flux
        PhysicalQuantities::MolarEnergyFlux Jz;
        std::array<PhysicalQuantities::MomentumFlux, 3> JzP;
        std::array<PhysicalQuantities::MomentumFlux, 3> JzL;
        PhysicalQuantities::CurrentDensity Jc_total;
        PhysicalQuantities::CurrentDensity Jc_cation;
        PhysicalQuantities::CurrentDensity Jc_anion;

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

        PhysicalQuantities::Length slabWidth;
        PhysicalQuantities::Length boxSize;

        double percentageOfKicksFailed;
    };

    using RNEMDInferredParametersPtr = std::shared_ptr<RNEMDInferredParameters>;


    struct RNEMDParameters
    {
        RNEMDBlockParametersPtr block { std::make_shared<RNEMDBlockParameters>() };
        RNEMDReportParametersPtr report { std::make_shared<RNEMDReportParameters>() };
        RNEMDInferredParametersPtr inferred { std::make_shared<RNEMDInferredParameters>() };
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
