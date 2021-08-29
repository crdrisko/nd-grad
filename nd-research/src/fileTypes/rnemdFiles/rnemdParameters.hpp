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

#include <common-utils/math.hpp>
#include <cpp-units/physicalQuantities.hpp>

namespace ND_Research
{
    struct RNEMDParameters
    {
        struct RNEMDBlockParameters
        {
            std::string exchangeMethod;
            std::string fluxType;

            char privilegedAxis;
            CppUnits::Time exchangeTime;
            std::vector<std::string> objectSelection;
            std::array<CppUnits::Length, 2> selectionA;
            std::array<CppUnits::Length, 2> selectionB;
            std::vector<std::string> outputSelection;
        };

        struct RNEMDReportParameters
        {
            CppUnits::Time runningTime;

            // Target fluxes
            CppUnits::MolarEnergyFlux kineticFlux;
            DryChem::Vector3D<CppUnits::MomentumFlux> momentumFlux;
            DryChem::Vector3D<CppUnits::MomentumFlux> angularMomentumFlux;
            CppUnits::CurrentDensity currentDensity;

            // Target one-time exchanges
            CppUnits::MolarEnergy kineticTarget;
            DryChem::Vector3D<CppUnits::Momentum> momentumTarget;
            DryChem::Vector3D<CppUnits::Momentum> angularMomentumTarget;

            // Actual exchange totals
            CppUnits::MolarEnergy kineticExchange;

            DryChem::Vector3D<CppUnits::Momentum> momentumExchange;
            DryChem::Vector3D<CppUnits::Momentum> angularMomentumExchange;

            // Actual fluxes
            CppUnits::MolarEnergyFlux Jz;
            DryChem::Vector3D<CppUnits::MomentumFlux> JzP;
            DryChem::Vector3D<CppUnits::MomentumFlux> JzL;
            CppUnits::CurrentDensity Jc_total;
            CppUnits::CurrentDensity Jc_cation;
            CppUnits::CurrentDensity Jc_anion;

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

            CppUnits::Length slabWidth;
            CppUnits::Length boxSize;

            double percentageOfKicksFailed {};
        };

        RNEMDBlockParameters block;
        RNEMDReportParameters report;
        RNEMDInferredParameters inferred;
    };

    using RNEMDParametersPtr = std::shared_ptr<RNEMDParameters>;


    struct RNEMDData
    {
        std::vector<CppUnits::Length> rnemdAxis;
        std::vector<CppUnits::Temperature> temperature;
        DryChem::Vector3D<std::vector<CppUnits::Velocity>> velocity;
        DryChem::Vector3D<std::vector<CppUnits::AngularVelocity>> angularVelocity;
        std::vector<CppUnits::MassDensity> density;
        std::vector<std::vector<CppUnits::Concentration>> activity;
        DryChem::Vector3D<std::vector<CppUnits::ElectricField>> electricField;
        std::vector<CppUnits::ElectricPotential> electricPotential;
    };

    using RNEMDDataPtr = std::shared_ptr<RNEMDData>;
}   // namespace ND_Research

#endif
