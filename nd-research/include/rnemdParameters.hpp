// Copyright (c) 2020-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: rnemdParameters.hpp
// Author: crdrisko
// Date: 11/22/2022-08:27:22
// Description:

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_RNEMDPARAMETERS_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_RNEMDPARAMETERS_HPP

#include <array>
#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <common-utils/math.hpp>
#include <cpp-units/physicalQuantities.hpp>

namespace ND_Research
{
    using ParticleFlux = CppUnits::PhysicalQuantity<CppUnits::Dimensionality<-2, 0, -1>>;

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
            ParticleFlux particleFlux;
            CppUnits::CurrentDensity currentDensity;

            // Target one-time exchanges
            CppUnits::MolarEnergy kineticTarget;
            DryChem::Vector3D<CppUnits::Momentum> momentumTarget;
            DryChem::Vector3D<CppUnits::Momentum> angularMomentumTarget;
            CppUnits::DimensionlessQuantity particleTarget;
            CppUnits::ElectricCharge electronTarget;

            // Actual exchange totals
            CppUnits::MolarEnergy kineticExchange;
            DryChem::Vector3D<CppUnits::Momentum> momentumExchange;
            DryChem::Vector3D<CppUnits::Momentum> angularMomentumExchange;
            CppUnits::DimensionlessQuantity particleExchange;
            CppUnits::ElectricCharge electronExchange;


            // Actual fluxes
            CppUnits::MolarEnergyFlux Jz;
            DryChem::Vector3D<CppUnits::MomentumFlux> JzP;
            DryChem::Vector3D<CppUnits::MomentumFlux> JzL;
            ParticleFlux Jp;
            CppUnits::CurrentDensity Jc;

            // Exchange statistics
            unsigned long trialCount {};
            unsigned long failTrialCount {};
            unsigned long failRootCount {};
        };

        struct RNEMDInferredParameters
        {
            bool hasSelectionB {false};
            bool useChargedSPF_ {false};
            std::size_t numberOfSelected {};
            std::unordered_map<std::string, int> names2index;
            std::string dataLabels {};

            int boundaryA_start {};
            int boundaryA_end {};
            int boundaryB_start {};
            int boundaryB_end {};
        };

        RNEMDBlockParameters block;
        RNEMDReportParameters report;
        RNEMDInferredParameters inferred;
    };

    struct RNEMDData
    {
        std::vector<CppUnits::Length> rnemdAxis;
        std::vector<CppUnits::Temperature> temperature;
        std::vector<DryChem::Vector3D<CppUnits::Velocity>> velocity;
        std::vector<DryChem::Vector3D<CppUnits::AngularVelocity>> angularVelocity;
        std::vector<CppUnits::MassDensity> density;
        std::vector<std::vector<CppUnits::Concentration>> activity;
        std::vector<DryChem::Vector3D<CppUnits::ElectricField>> electricField;
        std::vector<CppUnits::ElectricPotential> electricPotential;
    };
}   // namespace ND_Research

#endif
