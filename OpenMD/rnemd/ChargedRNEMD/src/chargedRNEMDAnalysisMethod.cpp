// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDAnalysisMethod.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/19/2020-12:43:05
// Description: Internal implementation details for the ChargedRNEMDAnalysisMethod class

#include <iomanip>
#include <fstream>
#include "../include/chargedRNEMDAnalysisMethod.hpp"

using std::vector;
using namespace Utilities_API::PhysicalQuantities;

namespace OpenMD::RNEMD::ChargedRNEMD
{
    struct ChargedRNEMDAnalysisMethod::InternalCalculations
    {
        Energy calculateElectrochemicalPotential(Temperature temperature, Concentration conc,
            ElectricPotential Phi, ElectricCharge charge) const;

        ElectricConductivity calculateElectricalConductivity(CurrentDensity Jc, ElectricCharge q_ion,
            Force gradientOfElectrochemcialPotential) const;

        MolarConductivity calculateMolarConductivity(ElectricConductivity sigma_ion,
            const std::vector<Concentration>& conc_ion) const;

        Mobility calculateMobility(MolarConductivity lambda_ion, ElectricCharge q_ion) const;
    };


    Energy ChargedRNEMDAnalysisMethod::InternalCalculations::calculateElectrochemicalPotential(
        Temperature temperature, Concentration conc, ElectricPotential Phi, ElectricCharge charge) const
    {
        Energy diffusionContribution
            = Constants::boltzmannConstant.convertQuantity(Conversions::getEnergyConversionFactor("J", "eV"))
                * temperature * conc.takeNaturalLogarithm();

        Energy electricFieldContribution
            = Phi.convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol", "eV_part")) * charge;

        return diffusionContribution + electricFieldContribution;
    }


    ElectricConductivity ChargedRNEMDAnalysisMethod::InternalCalculations::calculateElectricalConductivity(
        CurrentDensity Jc, ElectricCharge q_ion, Force gradientOfElectrochemcialPotential) const
    {
        ElectricConductivity sigma_ion = Calculations::calculateElectricalConductivity(q_ion, Jc,
            gradientOfElectrochemcialPotential);

        if ( sigma_ion < ElectricConductivity(0.0) )
            sigma_ion = sigma_ion.negateQuantity();

        return sigma_ion
            .convertQuantity(Conversions::getElectricChargeConversionFactor("e", "C"))
            .convertQuantity(1.0_ / Conversions::getLengthConversionFactor("Ang", "m"))
            .convertQuantity(1.0_ / Conversions::getSIPrexixConversionFactor("femto", "base"));
    }


    MolarConductivity ChargedRNEMDAnalysisMethod::InternalCalculations::calculateMolarConductivity(
        ElectricConductivity sigma_ion, const std::vector<Concentration>& conc_ion) const
    {
        Concentration averageConcentration { Mathematics::mathematicalFunction(conc_ion,
            Mathematics::calculateAverage) };

        MolarConductivity lambda_ion = Calculations::calculateMolarConductivity(sigma_ion,
            averageConcentration);

        return lambda_ion
            .convertQuantity(Conversions::getVolumeConversionFactor("L", "m3"))
            .convertQuantity(Conversions::getSIPrexixConversionFactor("base", "centi").raisePower(2));
    }


    Mobility ChargedRNEMDAnalysisMethod::InternalCalculations::calculateMobility(MolarConductivity lambda_ion,
        ElectricCharge q_ion) const
    {
        Mobility mobility_ion = Calculations::calculateMobility(lambda_ion, q_ion);

        return mobility_ion
            .convertQuantity(Conversions::getSIPrexixConversionFactor("centi", "base").raisePower(2));
    }


    ChargedRNEMDAnalysisMethod::ChargedRNEMDAnalysisMethod(const ChargedRNEMDFilePtr& RNEMDFile)
        : p_Impl{ std::make_unique<InternalCalculations>() }, rnemdFile{RNEMDFile}
    {
        RNEMDRegionPtr rnemdRegionData { std::make_shared<RNEMDRegion>(rnemdFile) };

        rnemdParameters = rnemdFile->getChargedRNEMDParameters();
        individualRegionData = rnemdRegionData->getRegionSpecificData();
    }


    ChargedRNEMDAnalysisMethod::ChargedRNEMDAnalysisMethod(std::string_view FullFileName)
        : ChargedRNEMDAnalysisMethod{ std::make_shared<ChargedRNEMDFile>(FullFileName) } {}


    ChargedRNEMDAnalysisMethod::~ChargedRNEMDAnalysisMethod() = default;


    void ChargedRNEMDAnalysisMethod::calculateElectricPotential(const size_t& referencePoint)
    {
        /* Due to the dependence on z when taking the integral of Ez, the Electric Potential values in the
            .rnemd file cannot be used with this method, so we implement our own integral here */
        vector<Length> z;
        vector<ElectricField> Ez;
        vector<ElectricPotential> Phi;

        for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
        {
            for (size_t i {}; i < individualRegionData[region - 1]->rnemdAxis.size(); ++i)
            {
                z.push_back(individualRegionData[region - 1]->rnemdAxis[i]);
                Ez.push_back(individualRegionData[region - 1]->electricField[2][i]);
            }
        }

        Phi = Mathematics::mathematicalFunction<ElectricPotential, int>(z, Ez, referencePoint,
            Mathematics::cumulativeTrapz);

        size_t runningIndex {};

        for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
        {
            for (size_t i {}; i < individualRegionData[region - 1]->rnemdAxis.size(); ++i)
            {
                individualRegionData[region - 1]->electricPotential[i] = Phi[runningIndex];

                ++runningIndex;
            }
        }
    }


    void ChargedRNEMDAnalysisMethod::calculateElectrochemicalPotential()
    {
        for (const auto& ion : rnemdParameters->ionicSpecies)
        {
            vector< vector<Energy> > externalTemporaryStorageVector;

            for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
            {
                vector<Energy> internalTemporaryStorageVector;

                for (size_t i {}; i < individualRegionData[region - 1]->rnemdAxis.size(); ++i)
                {
                    internalTemporaryStorageVector.push_back(
                        p_Impl->calculateElectrochemicalPotential(
                            individualRegionData[region - 1]->temperature[i],
                            individualRegionData[region - 1]->activity[ion->getIonIndex()][i],
                            individualRegionData[region - 1]->electricPotential[i],
                            ion->getIonCharge()) );
                }

                externalTemporaryStorageVector.push_back(internalTemporaryStorageVector);
            }

            electrochemicalPotential.push_back(externalTemporaryStorageVector);
        }
    }


    void ChargedRNEMDAnalysisMethod::calculateTransportProperties()
    {
        for (const auto& ion : rnemdParameters->ionicSpecies)
        {
            vector<ElectricConductivity> sigmaTemporaryStorageVector;
            vector<MolarConductivity> lambdaTemporaryStorageVector;
            vector<Mobility> mobilityTemporaryStorageVector;

            for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
            {
                CurrentDensity Jc_ion = (ion->getIonCharge() < 0.0_e ) ? rnemdParameters->report->Jc_anion
                    : rnemdParameters->report->Jc_cation;

                vector<Concentration> conc_ion = individualRegionData[region - 1]->
                    activity[ion->getIonIndex()];

                sigmaTemporaryStorageVector.push_back(
                    p_Impl->calculateElectricalConductivity(Jc_ion, ion->getIonCharge(),
                        gradientOfElectrochemicalPotential[ion->getIonIndex()][region - 1]) );

                lambdaTemporaryStorageVector.push_back(
                    p_Impl->calculateMolarConductivity(sigmaTemporaryStorageVector[region - 1], conc_ion) );

                mobilityTemporaryStorageVector.push_back(
                    p_Impl->calculateMobility(lambdaTemporaryStorageVector[region - 1], ion->getIonCharge()) );
            }

            sigma.push_back(sigmaTemporaryStorageVector);
            lambda.push_back(lambdaTemporaryStorageVector);
            mobility.push_back(mobilityTemporaryStorageVector);
        }
    }


    void ChargedRNEMDAnalysisMethod::printOutputToFile()
    {
        std::string outputFileName { rnemdFile->getFileName()->getFullFileName() };
        outputFileName = outputFileName.replace(outputFileName.find(".rnemd"), 6, ".ecp");

        std::ofstream outputFile;
        outputFile.open(outputFileName);

        outputFile << "# FileName = " << outputFileName << "\n";
        outputFile << "# FluxType = " << rnemdParameters->block->fluxType << "\n";
        outputFile << "# BoxSize = " << rnemdParameters->inferred->boxSize << "\n";
        outputFile << "# SlabWidth = " << rnemdParameters->inferred->slabWidth << "\n";
        outputFile << "# Jc anion = " << rnemdParameters->report->Jc_anion << " (e/Ang^2/fs)\n";
        outputFile << "# Jc cation = " << rnemdParameters->report->Jc_cation << " (e/Ang^2/fs)\n";
        outputFile << "# Percentage Of Kicks Failed = " <<
            ( static_cast<double>(rnemdParameters->report->failTrialCount)
                / static_cast<double>(rnemdParameters->report->trialCount) ) * 100 << "%\n#\n";

        for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
        {
            outputFile << "############################################ Region " << region
                       << " Data ############################################\n";

            printAdditionalRegionHeader(outputFile, region);

            outputFile << "# Transport Properties:\n";
            for (const auto& ion : rnemdParameters->ionicSpecies)
            {
                outputFile << "#   " << ion->getIonName() << ":\n";
                outputFile << "#     Ionic Conductivity " << " = "
                           << sigma[ion->getIonIndex()][region - 1] << " (S/m)\n";
                outputFile << "#     Molar Conductivity " << " = "
                           << lambda[ion->getIonIndex()][region - 1] << " (S cm^2/mol)\n";
                outputFile << "#     Ionic Mobility " << "     = "
                           << mobility[ion->getIonIndex()][region - 1] << " (m^2/V/s)\n";
            }

            outputFile << "#\n# z (Ang)\t Temp (K)\t";
            for (const auto& ion : rnemdParameters->ionicSpecies)
                outputFile << " [" << ion->getIonName() << "] (M)\t";
            outputFile << " Ez (V/Ang)\t Phi (V)\t";
            for (const auto& ion : rnemdParameters->ionicSpecies)
                outputFile << " ECP " << ion->getIonName() << " (eV)\t";
            outputFile << "\n";

            for (size_t i {}; i < individualRegionData[region - 1]->rnemdAxis.size(); ++i)
            {
                outputFile
                    << std::setw(8) << individualRegionData[region - 1]->rnemdAxis[i] << "\t"
                    << std::setw(8) << individualRegionData[region - 1]->temperature[i] << "\t";

                    for (const auto& ion : rnemdParameters->ionicSpecies)
                        outputFile
                            << std::setw(8)
                            << individualRegionData[region - 1]->activity[ion->getIonIndex()][i]
                            << "\t";;

                    outputFile
                        << std::setw(8)
                        << individualRegionData[region - 1]->electricField[2][i]
                            .convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol", "eV_part"))
                        << "\t"
                        << std::setw(8)
                        << individualRegionData[region - 1]->electricPotential[i]
                            .convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol", "eV_part"))
                        << "\t";

                    for (const auto& ion : rnemdParameters->ionicSpecies)
                        outputFile
                            << std::setw(8) << electrochemicalPotential[ion->getIonIndex()][region - 1][i]
                            << "\t";

                    outputFile << "\n";
            }

            outputFile << "\n";
        }
    }


    void ChargedRNEMDAnalysisMethod::process()
    {
        preProcess();

        calculateElectricPotential();

        calculateElectrochemicalPotential();

        calculateGradientOfElectrochemicalPotential();

        calculateTransportProperties();

        postProcess();

        printOutputToFile();
    }
}
