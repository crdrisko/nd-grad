// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/11/2020-12:42:57
// Description: Main ChargedRNEMD program, takes a rnemd file as input and returns the analysis in a ecp file

#include <iomanip>
#include <utilities-api/files.hpp>
#include "../include/chargedRNEMDFile.hpp"

using namespace OpenMD::RNEMD::ChargedRNEMD;
using namespace Utilities_API::PhysicalQuantities;

Energy calculateElectrochemicalPotential(Temperature temperature, Concentration conc, ElectricPotential Phi,
    ElectricCharge charge);

ElectricConductivity calculateElectricalConductivity(CurrentDensity Jc, ElectricCharge q_ion, 
    Force gradientOfElectrochemcialPotential);

int main(int argc, char* argv[])
{
    if (argc != 1)
        Utilities_API::Errors::printFatalErrorMessage(1, "The only valid command-line option is the filename.");

    Utilities_API::Files::FileNamePtr fileName { std::make_shared<Utilities_API::Files::FileName>(argv[1]) };

    if ( fileName->getFileExtension() != "rnemd" )
        Utilities_API::Errors::printFatalErrorMessage(1, "ChargedRNEMD input requires a valid .rnemd file.");

    ChargedRNEMDFilePtr rnemdFile { std::make_shared<ChargedRNEMDFile>(fileName->getFullFileName()) };
    ChargedRNEMDParametersPtr rnemdParameters { rnemdFile->getChargedRNEMDParameters() };
    std::vector<OpenMD::RNEMD::RNEMDDataPtr> individualRegionData { rnemdFile->getIndividualRegionData() };


    /* Due to the dependence on z when taking the integral of Ez, the Electric Potential values in the .rnemd
        cannot be used with this method, so we implement our own integral here */
    std::vector<Length> z;
    std::vector<ElectricField> Ez;
    std::vector<ElectricPotential> Phi;

    for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
        for (size_t i {}; i < individualRegionData[region - 1]->rnemdAxis.size(); ++i)
        {
            z.push_back(individualRegionData[region - 1]->rnemdAxis[i]);
            Ez.push_back(individualRegionData[region - 1]->electricField[2][i]);
        }
    
    Phi = Mathematics::mathematicalFunction<Length, ElectricField, int, ElectricPotential>
        (z, Ez, 0, Mathematics::cumulativeTrapz);       // Shift to the middle of the box as the reference point


    std::vector< std::vector<Energy> > electrochemicalPotential_anion;
    std::vector< std::vector<Energy> > electrochemicalPotential_cation;

    size_t runningIndex {};

    for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
    {
        std::vector<Energy> temporaryStorageVector_anion;
        std::vector<Energy> temporaryStorageVector_cation;

        for (size_t i {}; i < individualRegionData[region - 1]->rnemdAxis.size(); ++i)
        {
            temporaryStorageVector_anion.push_back( calculateElectrochemicalPotential(
                individualRegionData[region - 1]->temperature[i],
                individualRegionData[region - 1]->activity[rnemdParameters->anion->getIonIndex()][i],
                Phi[runningIndex],
                rnemdParameters->anion->getIonCharge()) );

            temporaryStorageVector_cation.push_back( calculateElectrochemicalPotential(
                individualRegionData[region - 1]->temperature[i],
                individualRegionData[region - 1]->activity[rnemdParameters->cation->getIonIndex()][i],
                Phi[runningIndex],
                rnemdParameters->cation->getIonCharge()) );
        }

        electrochemicalPotential_anion.push_back(temporaryStorageVector_anion);
        electrochemicalPotential_cation.push_back(temporaryStorageVector_cation);

        ++runningIndex;
    }


    std::vector< std::map<std::string, long double> > fittingParameters_anion;
    std::vector< std::map<std::string, long double> > fittingParameters_cation;

    for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
    {
        fittingParameters_anion.push_back( 
            Mathematics::mathematicalFunction< Length, Energy, std::map<std::string, long double> >
                (individualRegionData[region - 1]->rnemdAxis, electrochemicalPotential_anion[region - 1], 
                    Mathematics::linearLeastSquaresFitting) );

        fittingParameters_cation.push_back(
            Mathematics::mathematicalFunction< Length, Energy, std::map<std::string, long double> >
                (individualRegionData[region - 1]->rnemdAxis, electrochemicalPotential_cation[region - 1], 
                    Mathematics::linearLeastSquaresFitting) );
    }


    std::string outputFileName { fileName->getFullFileName() };
    outputFileName = outputFileName.replace(outputFileName.find_last_of("rnemd"), 5, "ecp");

    std::ofstream newFile;
    newFile.open (outputFileName);
    newFile << "# FileName: " << outputFileName << "\n";
    newFile << "# FluxType: " << rnemdParameters->block->fluxType << "\n";
    newFile << "# BoxSize: " << rnemdParameters->inferred->boxSize << "\n";
    newFile << "# SlabWidth: " << rnemdParameters->inferred->slabWidth << "\n";
    newFile << "# Jc " << rnemdParameters->anion->getIonName() << " = "
            << rnemdParameters->report->Jc_anion << " (e/Ang^2/fs)\n";
    newFile << "# Jc " << rnemdParameters->cation->getIonName() << " = "
            << rnemdParameters->report->Jc_cation << " (e/Ang^2/fs)\n\n";

    runningIndex = 0;

    for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
    {
        newFile << "############################################ Region " << region
                << " Data ############################################\n";
        newFile << "# Ionic Conductivity " << rnemdParameters->anion->getIonName()
                << " = "<< calculateElectricalConductivity(
                    rnemdParameters->report->Jc_anion, rnemdParameters->anion->getIonCharge(), 
                    Force(fittingParameters_anion[region - 1]["slope"]) ) << " (S/m)\n";
        newFile << "# Ionic Conductivity " << rnemdParameters->cation->getIonName()
                << " = "<< calculateElectricalConductivity(
                    rnemdParameters->report->Jc_cation, rnemdParameters->cation->getIonCharge(), 
                    Force(fittingParameters_cation[region - 1]["slope"]) ) << " (S/m)\n";
        newFile << "# Molar Conductivity " << rnemdParameters->anion->getIonName()
                << " = LAMBDA_ANION (S cm^2/mol)\n";
        newFile << "# Molar Conductivity " << rnemdParameters->cation->getIonName()
                << " = LAMBDA_CATION (S cm^2/mol)\n";
        newFile << "# Ionic Mobility " << rnemdParameters->anion->getIonName()
                << "     = MOBILITY_ANION (m^2/V/s)\n";
        newFile << "# Ionic Mobility " << rnemdParameters->cation->getIonName()
                << "     = MOBILITY_CATION (m^2/V/s)\n\n";
        newFile << "# z (Ang)\t Temp (K)\t [" << rnemdParameters->anion->getIonName() << "] (M)\t ["
                << rnemdParameters->cation->getIonName() << "] (M)\t Ez (V/Ang)\t Phi (V)\t ECP "
                << rnemdParameters->anion->getIonName() << " (eV)\t ECP "
                << rnemdParameters->cation->getIonName() << " (eV)\n";

        for (size_t i {}; i < individualRegionData[region - 1]->rnemdAxis.size(); ++i)
        {
            newFile
                << std::setw(8) << individualRegionData[region - 1]->rnemdAxis[i] << "\t"
                << std::setw(8) << individualRegionData[region - 1]->temperature[i] << "\t"
                << std::setw(8) << individualRegionData[region - 1]->
                                        activity[rnemdParameters->anion->getIonIndex()][i] << "\t"
                << std::setw(8) << individualRegionData[region - 1]->
                                        activity[rnemdParameters->cation->getIonIndex()][i] << "\t"
                << std::setw(8) << individualRegionData[region - 1]->electricField[2][i].convertQuantity(
                    Conversions::getMolarEnergyConversionFactor("kcal_mol", "eV_part")) << "\t"
                << std::setw(8) << Phi[runningIndex].convertQuantity(
                    Conversions::getMolarEnergyConversionFactor("kcal_mol", "eV_part")) << "\t"
                << std::setw(8) << electrochemicalPotential_anion[region - 1][i] << "\t"
                << std::setw(8) << electrochemicalPotential_cation[region - 1][i] << "\n";

            ++runningIndex;
        }
    }

    newFile.close();
}


Energy calculateElectrochemicalPotential(Temperature temperature, Concentration conc, ElectricPotential Phi,
    ElectricCharge charge)
{
    Energy diffusionContribution
        = Constants::boltzmannConstant.convertQuantity(Conversions::getEnergyConversionFactor("J", "eV"))
            * temperature * conc.takeNaturalLogarithm();

    Energy electricFieldContribution
        = Phi.convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol", "eV_part")) * charge;

    return diffusionContribution + electricFieldContribution;
}


ElectricConductivity calculateElectricalConductivity(CurrentDensity Jc_ion, ElectricCharge q_ion, 
    Force gradientOfElectrochemcialPotential)
{
    ElectricConductivity sigma_ion = q_ion * Jc_ion / gradientOfElectrochemcialPotential;
    
    return sigma_ion.negateQuantity()
        .convertQuantity(Conversions::getElectricChargeConversionFactor("e", "C"))
        .convertQuantity(1.0_ / Conversions::getLengthConversionFactor("Ang", "m"))
        .convertQuantity(1.0_ / Conversions::getSIPrexixConversionFactor("femto", "base")); 
}