// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdParameters.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/20/2020-15:44:50
// Description: Defines data structures dedicated to holding the data from a given RNEMD file

#ifndef RNEMDPARAMETERS_HPP
#define RNEMDPARAMETERS_HPP

#include <memory>
#include <vector>
#include <string>
#include <array>
#include <utilities-api/utilities-api.hpp>

namespace OpenMD::RNEMD
{
    // Including the namespaces in this scope greatly simplifies readability
    using namespace Utilities_API::PhysicalQuantities::ElectromagneticQuantities;
    using namespace Utilities_API::PhysicalQuantities::MKSQuantities;
    using namespace Utilities_API::PhysicalQuantities::MolarQuantities;
    using namespace Utilities_API::PhysicalQuantities::TemperatureQuantities;

    struct RNEMDBlockParameters
    {
        std::string exchangeMethod;
        std::string fluxType;

        std::string privilegedAxis;
        Time exchangeTime;
        std::vector<std::string> objectSelection;
        std::array<Length, 2> selectionA;
        std::array<Length, 2> selectionB;
        std::vector<std::string> outputSelection;
    };

    using RNEMDBlockParametersPtr = std::shared_ptr<RNEMDBlockParameters>;


    struct RNEMDReportParameters
    {
        Time runningTime;

        // Target flux
        MolarEnergyFlux kineticFlux;
        std::array<MomentumFlux, 3> momentumFlux;
        std::array<MomentumFlux, 3> angularMomentumFlux;                // Angular Momentum Flux ??
        CurrentDensity currentDensity;

        // Target one-time exchanges
        MolarEnergy kineticTarget;
        std::array<Momentum, 3> momentumTarget;
        std::array<Momentum, 3> angularMomentumTarget;                  // Angular Momentum ??

        // Actual exchange totals
        MolarEnergy kineticExchange;
        std::array<Momentum, 3> momentumExchange;
        std::array<Momentum, 3> angularMomentumExchange;                // Angular Momentum  ??

        // Actual flux
        MolarEnergyFlux Jz;
        std::array<MomentumFlux, 3> JzP;
        std::array<MomentumFlux, 3> JzL;                                // Angular Momentum Flux ??
        CurrentDensity Jc_total;
        CurrentDensity Jc_cation;
        CurrentDensity Jc_anion;

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

        Length slabWidth;
        Length boxSize;
    };

    using RNEMDInferredParametersPtr = std::shared_ptr<RNEMDInferredParameters>;


    struct RNEMDData
    {
        std::vector<std::string> dataLabels { "z(Angstroms)",
                                              "R(Angstroms)",
                                              "Temperature(K)",
                                              "Velocity(angstroms/fs)",
                                              "AngularVelocity(angstroms^2/fs)",
                                              "Density(g cm^-3)",
                                              "Activity(unitless)",
                                              "Electrical Field(kcal/mol/angstroms/e)" };

        std::vector<Length> rnemdAxis;                              // x, y, or z
        std::vector<Length> radius;
        std::vector<Temperature> temperature;
        std::array<std::vector<Velocity>, 3> velocity;              // x, y, and z directions
        std::array<std::vector<Velocity>, 3> angularVelocity;       // x, y, and z directions
        std::vector<MassDensity> density;
        std::vector< std::vector<Concentration> > activity;         // species 1, species 2, ..., species n
        std::array<std::vector<ElectricField>, 3> electricField;    // x, y, and z directions
    };

    using RNEMDDataPtr =  std::shared_ptr<RNEMDData>;
}

#endif
