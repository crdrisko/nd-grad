// Copyright (c) 2020-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: rnemdFile.cpp
// Author: crdrisko
// Date: 11/22/2022-08:32:58
// Description:

#include "rnemdFile.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <common-utils/files.hpp>
#include <common-utils/strings.hpp>
#include <cpp-units/physicalQuantities.hpp>
#include <dryphys/utilities.hpp>

using namespace CppUnits;
using namespace DryPhys::Literals;

namespace ND_Research
{
    void RNEMDFile::operator()(const std::string& fileContents_)
    {
        DryChem::AsRows rowParser {};
        std::vector<std::string> rows {rowParser(fileContents_)};

        std::string dataContents {}, errorContents {};
        std::string punctuation {",:; \t\n"};

        bool targetFluxes {false}, targetExchanges {false}, actualExchange {false}, actualFluxes {false};

        for (const auto& row : rows)
        {
            if (row[0] == '#')
            {
                if (DryChem::foundSubstr("Target", row))
                {
                    if (DryChem::foundSubstr("flux", row))
                    {
                        targetFluxes    = true;
                        targetExchanges = false;
                        actualExchange  = false;
                        actualFluxes    = false;
                    }
                    else if (DryChem::foundSubstr("one-time", row))
                    {
                        targetFluxes    = false;
                        targetExchanges = true;
                        actualExchange  = false;
                        actualFluxes    = false;
                    }
                }
                else if (DryChem::foundSubstr("Actual", row))
                {
                    if (DryChem::foundSubstr("exchange", row))
                    {
                        targetFluxes    = false;
                        targetExchanges = false;
                        actualExchange  = true;
                        actualFluxes    = false;
                    }
                    else if (DryChem::foundSubstr("flux", row))
                    {
                        targetFluxes    = false;
                        targetExchanges = false;
                        actualExchange  = false;
                        actualFluxes    = true;
                    }
                }
                else if (DryChem::foundSubstr('=', row))
                {
                    DryChem::Tokenizer tok {row, punctuation};
                    std::vector<std::string> splitRow = tok.split();

                    switch (DryPhys::djb2Hash(splitRow[1].c_str()))
                    {
                    case "exchangeMethod"_sID:
                    {
                        params_.block.exchangeMethod = removeQuotes(splitRow[3]);
                        break;
                    }
                    case "fluxType"_sID:
                    {
                        params_.block.fluxType = removeQuotes(splitRow[3]);
                        break;
                    }
                    case "privilegedAxis"_sID:
                    {
                        params_.block.privilegedAxis = splitRow[3][0];
                        break;
                    }
                    case "exchangeTime"_sID:
                    {
                        params_.block.exchangeTime = Time {splitRow[3]};
                        break;
                    }
                    case "objectSelection"_sID:
                    {   // Loop from quotation to quotation
                        for (std::size_t i {3}; i < splitRow.size(); ++i)
                        {
                            params_.block.objectSelection.push_back(removeQuotes(splitRow[i]));
                        }
                        break;
                    }
                    case "selectionA"_sID:
                    {
                        params_.block.selectionA[0] = Length {splitRow[6]};

                        if (splitRow[4] == "r")
                            continue;

                        params_.block.selectionA[1] = Length {splitRow[10]};

                        break;
                    }
                    case "selectionB"_sID:
                    {
                        if (splitRow[4] == "none")
                        {
                            params_.inferred.hasSelectionB = false;
                        }
                        else if (splitRow[4] == "hull")
                        {
                            params_.inferred.hasSelectionB = false;
                        }
                        else
                        {
                            params_.inferred.hasSelectionB = true;

                            params_.block.selectionB[0] = Length {splitRow[6]};
                            params_.block.selectionB[1] = Length {splitRow[10]};
                        }
                        break;
                    }
                    case "outputSelection"_sID:
                    {
                        // Loop from quotation to quotation
                        for (std::size_t i {3}; i < splitRow.size(); ++i)
                        {
                            params_.block.outputSelection.push_back(removeQuotes(splitRow[i]));
                        }
                        break;
                    }
                    case "running"_sID:
                    {
                        params_.report.runningTime = Time {splitRow[4]};
                        break;
                    }
                    case "kinetic"_sID:
                    {
                        if (targetFluxes)
                            params_.report.kineticFlux = MolarEnergyFlux {splitRow[3]};
                        else if (targetExchanges)
                            params_.report.kineticTarget = MolarEnergy {splitRow[3]};
                        else if (actualExchange)
                            params_.report.kineticExchange = MolarEnergy {splitRow[3]};
                        else if (actualFluxes)
                            params_.report.Jz = MolarEnergyFlux {splitRow[3]};

                        break;
                    }
                    case "momentum"_sID:
                    {
                        if (targetFluxes)
                            params_.report.momentumFlux = DryChem::Vector3D<MomentumFlux> {MomentumFlux {splitRow[4]},
                                MomentumFlux {splitRow[5]},
                                MomentumFlux {splitRow[6]}};
                        else if (targetExchanges)
                            params_.report.momentumTarget = DryChem::Vector3D<Momentum> {Momentum {splitRow[4]},
                                Momentum {splitRow[5]},
                                Momentum {splitRow[6]}};
                        else if (actualExchange)
                            params_.report.momentumExchange = DryChem::Vector3D<Momentum> {Momentum {splitRow[4]},
                                Momentum {splitRow[5]},
                                Momentum {splitRow[6]}};
                        else if (actualFluxes)
                            params_.report.JzP = DryChem::Vector3D<MomentumFlux> {MomentumFlux {splitRow[4]},
                                MomentumFlux {splitRow[5]},
                                MomentumFlux {splitRow[6]}};

                        break;
                    }
                    case "angular"_sID:
                    {
                        if (targetFluxes)
                            params_.report.angularMomentumFlux = DryChem::Vector3D<MomentumFlux> {MomentumFlux {splitRow[5]},
                                MomentumFlux {splitRow[6]},
                                MomentumFlux {splitRow[7]}};
                        else if (targetExchanges)
                            params_.report.angularMomentumTarget = DryChem::Vector3D<Momentum> {Momentum {splitRow[5]},
                                Momentum {splitRow[6]},
                                Momentum {splitRow[7]}};
                        else if (actualExchange)
                            params_.report.angularMomentumExchange = DryChem::Vector3D<Momentum> {Momentum {splitRow[5]},
                                Momentum {splitRow[6]},
                                Momentum {splitRow[7]}};
                        else if (actualFluxes)
                            params_.report.JzL = DryChem::Vector3D<MomentumFlux> {MomentumFlux {splitRow[5]},
                                MomentumFlux {splitRow[6]},
                                MomentumFlux {splitRow[7]}};

                        break;
                    }
                    case "particle"_sID:
                    {
                        if (targetFluxes)
                            params_.report.particleFlux = ParticleFlux {splitRow[3]};
                        else if (targetExchanges)
                            params_.report.particleTarget = DimensionlessQuantity {splitRow[3]};
                        else if (actualExchange)
                            params_.report.particleExchange = DimensionlessQuantity {splitRow[3]};
                        else if (actualFluxes)
                            params_.report.Jp = ParticleFlux {splitRow[3]};

                        params_.inferred.useChargedSPF_ = false;
                        break;
                    }
                    case "current"_sID:
                    {
                        if (targetFluxes)
                            params_.report.currentDensity = CurrentDensity {splitRow[4]};
                        else if (targetExchanges)
                            params_.report.electronTarget = ElectricCharge {splitRow[4]};
                        else if (actualExchange)
                            params_.report.electronExchange = ElectricCharge {splitRow[4]};
                        else if (actualFluxes)
                            params_.report.Jc = CurrentDensity {splitRow[4]};

                        params_.inferred.useChargedSPF_ = true;
                        break;
                    }
                    case "attempted"_sID:
                    {
                        params_.report.trialCount = std::stoul(splitRow[3]);
                        break;
                    }
                    case "failed"_sID:
                    {
                        params_.report.failTrialCount = std::stoul(splitRow[3]);
                        break;
                    }
                    case "NIVS"_sID:
                    {
                        params_.report.failRootCount = std::stoul(splitRow[5]);
                        break;
                    }
                    default:
                        break;
                    }
                }
                else if (DryChem::foundSubstr("(Angstroms)", row))
                {
                    std::string punctuation2 {")\t\n"};
                    DryChem::Tokenizer tok {row, punctuation2};
                    std::vector<std::string> splitRow = tok.split();

                    params_.inferred.dataLabels = row;

                    int index {};

                    for (const auto& elem : splitRow)
                    {
                        if (elem == "x(Angstroms" || elem == "y(Angstroms" || elem == "z(Angstroms")
                        {
                            params_.inferred.names2index["Z"] = index;
                            ++index;
                        }
                        else if (elem == "R(Angstroms")
                        {
                            params_.inferred.names2index["R"] = index;
                            ++index;
                        }
                        else if (elem == "Temperature(K")
                        {
                            params_.inferred.names2index["Temp"] = index;
                            ++index;
                        }
                        else if (elem == "Velocity(angstroms/fs")
                        {
                            params_.inferred.names2index["Vel"] = index;
                            index += 3;
                        }
                        else if (elem == "AngularVelocity(angstroms^2/fs")
                        {
                            params_.inferred.names2index["AngVel"] = index;
                            index += 3;
                        }
                        else if (elem == "Density(g cm^-3")
                        {
                            params_.inferred.names2index["Den"] = index;
                            ++index;
                        }
                        else if (DryChem::foundSubstr("Activity(unitless", elem))
                        {
                            determineActivity(row);

                            params_.inferred.names2index["Conc"] = index;
                            index += params_.inferred.numberOfSelected;
                        }
                        else if (elem == "Electric Field(kcal/mol/angstroms/e")
                        {
                            params_.inferred.names2index["EField"] = index;
                            index += 3;
                        }
                        else if (elem == "Electrostatic Potential(kcal/mol/e")
                        {
                            params_.inferred.names2index["EPot"] = index;
                            ++index;
                        }
                    }
                }
                else if (!DryChem::foundSubstr("##", row) && !DryChem::foundSubstr(":", row)
                         && !DryChem::foundSubstr("{", row) && !DryChem::foundSubstr("}", row))
                {
                    errorContents += row.substr(1, row.length() - 1) + '\n';
                }
            }
            else
            {
                dataContents += row + '\n';
            }
        }

        data_   = parseDataFields(dataContents);
        errors_ = parseDataFields(errorContents);

        // Infer Region Bounds from Selections A and B
        params_.inferred.boundaryA_start = determineRegionBounds(params_.block.selectionA[0]);
        params_.inferred.boundaryA_end   = determineRegionBounds(params_.block.selectionA[1]);

        if (params_.inferred.hasSelectionB)
        {
            params_.inferred.boundaryB_start = determineRegionBounds(params_.block.selectionB[0]);
            params_.inferred.boundaryB_end   = determineRegionBounds(params_.block.selectionB[1]);
        }
    }

    void RNEMDFile::determineActivity(const std::string& row)
    {
        const std::string activityLabel {"Activity(unitless)("};

        std::size_t start {row.find(activityLabel) + activityLabel.length()};
        std::size_t end {row.find_first_of(')', start)};

        std::string tempStr = row.substr(start, end - start);

        DryChem::Tokenizer tok {tempStr, ")\t\n"};
        auto tokens = tok.split();

        params_.inferred.numberOfSelected = tokens.size();
    }

    RNEMDData RNEMDFile::parseDataFields(const std::string& dataContents)
    {
        RNEMDData results;
        DryChem::AsColumns columnParser {};
        std::vector<std::string> columns {columnParser(dataContents)};

        if (params_.inferred.names2index.find("Z") != params_.inferred.names2index.end())
        {
            DryChem::Tokenizer tok {columns[params_.inferred.names2index["Z"]]};
            std::vector<std::string> splitColumns = tok.split();

            for (const auto& elem : splitColumns)
                results.rnemdAxis.emplace_back(elem);
        }

        if (params_.inferred.names2index.find("R") != params_.inferred.names2index.end())
        {
            DryChem::Tokenizer tok {columns[params_.inferred.names2index["R"]]};
            std::vector<std::string> splitColumns = tok.split();

            for (const auto& elem : splitColumns)
                results.rnemdAxis.emplace_back(elem);
        }

        if (params_.inferred.names2index.find("Temp") != params_.inferred.names2index.end())
        {
            DryChem::Tokenizer tok {columns[params_.inferred.names2index["Temp"]]};
            std::vector<std::string> splitColumns = tok.split();

            for (const auto& elem : splitColumns)
                results.temperature.emplace_back(elem);
        }

        if (params_.inferred.names2index.find("Vel") != params_.inferred.names2index.end())
        {
            bool firstPass {true};

            for (std::size_t i {}; i < 3; ++i)
            {
                DryChem::Tokenizer tok {columns[params_.inferred.names2index["Vel"] + i]};
                std::vector<std::string> splitColumns = tok.split();

                if (firstPass)
                {
                    results.velocity.resize(splitColumns.size());
                    firstPass = false;
                }

                for (std::size_t j {}; j < splitColumns.size(); ++j)
                    results.velocity[j][i] = Velocity {splitColumns[j]};
            }
        }

        if (params_.inferred.names2index.find("AngVel") != params_.inferred.names2index.end())
        {
            bool firstPass {true};

            for (std::size_t i {}; i < 3; ++i)
            {
                DryChem::Tokenizer tok {columns[params_.inferred.names2index["AngVel"] + i]};
                std::vector<std::string> splitColumns = tok.split();

                if (firstPass)
                {
                    results.angularVelocity.resize(splitColumns.size());
                    firstPass = false;
                }

                for (std::size_t j {}; j < splitColumns.size(); ++j)
                    results.angularVelocity[j][i] = AngularVelocity {splitColumns[j]};
            }
        }

        if (params_.inferred.names2index.find("Den") != params_.inferred.names2index.end())
        {
            DryChem::Tokenizer tok {columns[params_.inferred.names2index["Den"]]};
            std::vector<std::string> splitColumns = tok.split();

            for (const auto& elem : splitColumns)
                results.density.emplace_back(elem);
        }

        if (params_.inferred.names2index.find("Conc") != params_.inferred.names2index.end())
        {
            bool firstPass {true};

            for (std::size_t i {}; i < params_.inferred.numberOfSelected; ++i)
            {
                DryChem::Tokenizer tok {columns[params_.inferred.names2index["Conc"] + i]};
                std::vector<std::string> splitColumns = tok.split();

                if (firstPass)
                {
                    results.activity.resize(params_.inferred.numberOfSelected);
                    firstPass = false;
                }

                results.activity[i].resize(splitColumns.size());

                for (std::size_t j {}; j < splitColumns.size(); ++j)
                    results.activity[i][j] = Concentration {splitColumns[j]};
            }
        }

        if (params_.inferred.names2index.find("EField") != params_.inferred.names2index.end())
        {
            bool firstPass {true};

            for (std::size_t i {}; i < 3; ++i)
            {
                DryChem::Tokenizer tok {columns[params_.inferred.names2index["EField"] + i]};
                std::vector<std::string> splitColumns = tok.split();

                if (firstPass)
                {
                    results.electricField.resize(splitColumns.size());
                    firstPass = false;
                }

                for (std::size_t j {}; j < splitColumns.size(); ++j)
                    results.electricField[j][i] = ElectricField {splitColumns[j]};
            }
        }

        if (params_.inferred.names2index.find("EPot") != params_.inferred.names2index.end())
        {
            DryChem::Tokenizer tok {columns[params_.inferred.names2index["EPot"]]};
            std::vector<std::string> splitColumns = tok.split();

            for (const auto& elem : splitColumns)
                results.electricPotential.emplace_back(elem);
        }

        return results;
    }

    std::string RNEMDFile::removeQuotes(const std::string& str) const
    {
        std::string copyStr {str};
        copyStr.erase(std::remove(copyStr.begin(), copyStr.end(), '\"'), copyStr.end());

        return copyStr;
    }

    int RNEMDFile::determineRegionBounds(const CppUnits::Length& wrappedZCoords) const
    {
        CppUnits::Length region = ((data_.rnemdAxis.back() - data_.rnemdAxis.front()) / 2) + wrappedZCoords;

        return std::upper_bound(data_.rnemdAxis.begin(), data_.rnemdAxis.end(), (region - data_.rnemdAxis[0]))
               - data_.rnemdAxis.begin();
    }

    std::string RNEMDFile::generateSelectionScript(const std::vector<std::string>& selectionScript) const
    {
        std::string printableSelectionScript {"\""};
        for (const auto& str : selectionScript)
            printableSelectionScript += (str + ' ');
        printableSelectionScript.replace(printableSelectionScript.length() - 1, 1, "\"");

        return printableSelectionScript;
    }

    void RNEMDFile::writeRNEMDFile(const std::string& fileName) const
    {
        std::ofstream outputFile;
        outputFile.open(fileName);

        outputFile.precision(8);

        outputFile << "#######################################################\n";
        outputFile << "# RNEMD {\n";
        outputFile << "#    exchangeMethod  = \"" << params_.block.exchangeMethod << "\";\n";
        outputFile << "#    fluxType  = \"" << params_.block.fluxType << "\";\n";
        outputFile << "#    privilegedAxis = " << params_.block.privilegedAxis << ";\n";
        outputFile << "#    exchangeTime = " << params_.block.exchangeTime << ";\n";
        outputFile << "#    objectSelection = " << generateSelectionScript(params_.block.objectSelection) << ";\n";
        outputFile << "#    selectionA = \"select wrappedz >= " << params_.block.selectionA[0] << " && wrappedz < "
                   << params_.block.selectionA[1] << "\";\n";
        outputFile << "#    selectionB = \"select wrappedz >= " << params_.block.selectionB[0] << " || wrappedz < "
                   << params_.block.selectionB[1] << "\";\n";
        outputFile << "#    outputSelection = " << generateSelectionScript(params_.block.outputSelection) << ";\n";
        outputFile << "# }\n";
        outputFile << "#######################################################\n";
        outputFile << "# RNEMD report:\n";
        outputFile << "#      running time = " << static_cast<std::size_t>(params_.report.runningTime.getMagnitude())
                   << " fs\n";
        outputFile << "# Target flux:\n";
        outputFile << "#           kinetic = " << params_.report.kineticFlux << " (kcal/mol/A^2/fs)\n";
        outputFile << "#          momentum = " << generateVector3Ds(params_.report.momentumFlux) << " (amu/A/fs^2)\n";
        outputFile << "#  angular momentum = " << generateVector3Ds(params_.report.angularMomentumFlux)
                   << " (amu/A^2/fs^2)\n";
        if (!params_.inferred.useChargedSPF_)
            outputFile << "#          particle = " << params_.report.particleFlux << " (particles/A^2/fs)\n";
        else
            outputFile << "#   current density = " << params_.report.currentDensity << " (electrons/A^2/fs)\n";
        outputFile << "# Target one-time exchanges:\n";
        outputFile << "#          kinetic = " << params_.report.kineticTarget << " (kcal/mol)\n";
        outputFile << "#          momentum = " << generateVector3Ds(params_.report.momentumTarget) << " (amu*A/fs)\n";
        outputFile << "#  angular momentum = " << generateVector3Ds(params_.report.angularMomentumTarget)
                   << " (amu*A^2/fs)\n";
        if (!params_.inferred.useChargedSPF_)
            outputFile << "#          particle = " << params_.report.particleTarget << " (particles)\n";
        else
            outputFile << "#   current density = " << params_.report.electronTarget << " (electrons)\n";
        outputFile << "# Actual exchange totals:\n";
        outputFile << "#          kinetic = " << params_.report.kineticExchange << " (kcal/mol)\n";
        outputFile << "#          momentum = " << generateVector3Ds(params_.report.momentumExchange) << " (amu*A/fs)\n";
        outputFile << "#  angular momentum = " << generateVector3Ds(params_.report.angularMomentumExchange)
                   << " (amu*A^2/fs)\n";
        if (!params_.inferred.useChargedSPF_)
            outputFile << "#          particle = " << params_.report.particleExchange << " (particles)\n";
        else
            outputFile << "#   current density = " << params_.report.electronExchange << " (electrons)\n";
        outputFile << "# Actual flux:\n";
        outputFile << "#          kinetic = " << params_.report.Jz << " (kcal/mol/A^2/fs)\n";
        outputFile << "#          momentum = " << generateVector3Ds(params_.report.JzP) << " (amu/A/fs^2)\n";
        outputFile << "#  angular momentum = " << generateVector3Ds(params_.report.JzL) << " (amu/A^2/fs^2)\n";
        if (!params_.inferred.useChargedSPF_)
            outputFile << "#          particle = " << params_.report.Jp << " (particles/A^2/fs)\n";
        else
            outputFile << "#   current density = " << params_.report.Jc << " (electrons/A^2/fs)\n";
        outputFile << "# Exchange statistics:\n";
        outputFile << "#               attempted = " << params_.report.trialCount << "\n";
        outputFile << "#                  failed = " << params_.report.failTrialCount << "\n";
        if (params_.block.exchangeMethod == "NIVS")
            outputFile << "#  NIVS root-check errors = " << params_.report.failRootCount << "\n";
        outputFile << "#######################################################\n";
        outputFile << params_.inferred.dataLabels << '\n';

        for (std::size_t bin {}; bin < data_.rnemdAxis.size(); ++bin)
        {
            // These need to be sorted in the correct order before this is useful...
            if (auto search = params_.inferred.names2index.find("Z"); search != params_.inferred.names2index.end())
                outputFile << '\t' << data_.rnemdAxis[bin];

            if (auto search = params_.inferred.names2index.find("R"); search != params_.inferred.names2index.end())
                outputFile << '\t' << data_.rnemdAxis[bin];

            if (auto search = params_.inferred.names2index.find("Temp"); search != params_.inferred.names2index.end())
                outputFile << '\t' << data_.temperature[bin];

            if (auto search = params_.inferred.names2index.find("Vel"); search != params_.inferred.names2index.end())
                for (const auto& elem : data_.velocity[bin])
                    outputFile << '\t' << elem;

            if (auto search = params_.inferred.names2index.find("AngVel"); search != params_.inferred.names2index.end())
                for (const auto& elem : data_.angularVelocity[bin])
                    outputFile << '\t' << elem;

            if (auto search = params_.inferred.names2index.find("Den"); search != params_.inferred.names2index.end())
                outputFile << '\t' << data_.density[bin];

            if (auto search = params_.inferred.names2index.find("Conc"); search != params_.inferred.names2index.end())
                for (const auto& selection : data_.activity)
                    outputFile << '\t' << selection[bin];

            if (auto search = params_.inferred.names2index.find("EField"); search != params_.inferred.names2index.end())
                for (const auto& elem : data_.electricField[bin])
                    outputFile << '\t' << elem;

            if (auto search = params_.inferred.names2index.find("EPot"); search != params_.inferred.names2index.end())
                outputFile << '\t' << data_.electricPotential[bin];

            outputFile << '\n';
        }

        outputFile << "#######################################################\n"
                   << "# 95% confidence intervals in those quantities follow:\n"
                   << "#######################################################\n";

        for (std::size_t bin {}; bin < errors_.rnemdAxis.size(); ++bin)
        {
            outputFile << "#";

            // These need to be sorted in the correct order before this is useful...
            if (auto search = params_.inferred.names2index.find("Z"); search != params_.inferred.names2index.end())
                outputFile << '\t' << errors_.rnemdAxis[bin];

            if (auto search = params_.inferred.names2index.find("R"); search != params_.inferred.names2index.end())
                outputFile << '\t' << errors_.rnemdAxis[bin];

            if (auto search = params_.inferred.names2index.find("Temp"); search != params_.inferred.names2index.end())
                outputFile << '\t' << errors_.temperature[bin];

            if (auto search = params_.inferred.names2index.find("Vel"); search != params_.inferred.names2index.end())
                for (const auto& elem : errors_.velocity[bin])
                    outputFile << '\t' << elem;

            if (auto search = params_.inferred.names2index.find("AngVel"); search != params_.inferred.names2index.end())
                for (const auto& elem : errors_.angularVelocity[bin])
                    outputFile << '\t' << elem;

            if (auto search = params_.inferred.names2index.find("Den"); search != params_.inferred.names2index.end())
                outputFile << '\t' << errors_.density[bin];

            if (auto search = params_.inferred.names2index.find("Conc"); search != params_.inferred.names2index.end())
                for (const auto& selection : errors_.activity)
                    outputFile << '\t' << selection[bin];

            if (auto search = params_.inferred.names2index.find("EField"); search != params_.inferred.names2index.end())
                for (const auto& elem : errors_.electricField[bin])
                    outputFile << '\t' << elem;

            if (auto search = params_.inferred.names2index.find("EPot"); search != params_.inferred.names2index.end())
                outputFile << '\t' << errors_.electricPotential[bin];

            outputFile << '\n';
        }
    }
}   // namespace ND_Research
