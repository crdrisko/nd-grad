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

int main(int argc, char* argv[])
{
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

    Phi = advancedMathematicalFunctionCall<ElectricPotentialDimensionality>(cumulativeTrapz, z, Ez);


    std::string outputFileName { fileName->getFullFileName() };
    outputFileName = outputFileName.replace(outputFileName.find("rnemd"), 5, "ecp");

    std::ofstream newFile;
    newFile.open (outputFileName);
    newFile << "# FileName: " << outputFileName << "\n";
    newFile << "# FluxType: " << rnemdParameters->block->fluxType << "\n";
    newFile << "# BoxSize: " << rnemdParameters->inferred->boxSize << "\n";
    newFile << "# SlabWidth: " << rnemdParameters->inferred->slabWidth << "\n";
    newFile << "# Jc " << rnemdParameters->anion->getIonName() << " = "
            << rnemdParameters->report->Jc_anion
                .convertQuantity(Conversions::getElectricChargeConversionFactor("e", "C"))
                .convertQuantity(1.0_ / Conversions::getAreaConversionFactor("Ang2", "m2"))
                .convertQuantity(1.0_ / Conversions::getSIPrexixConversionFactor("femto", "base"))
            << " (e/Ang^2/fs)\n";
    newFile << "# Jc " << rnemdParameters->cation->getIonName() << " = "
            << rnemdParameters->report->Jc_cation
                .convertQuantity(Conversions::getElectricChargeConversionFactor("e", "C"))
                .convertQuantity(1.0_ / Conversions::getAreaConversionFactor("Ang2", "m2"))
                .convertQuantity(1.0_ / Conversions::getSIPrexixConversionFactor("femto", "base"))
            << " (e/Ang^2/fs)\n\n";

    size_t runningIndex {};

    for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
    {
        newFile << "############################################ Region " << region
                << " Data ############################################\n";
        newFile << "# Ionic Conductivity " << rnemdParameters->anion->getIonName()
                << " = SIGMA_ANION (S/m)\n";
        newFile << "# Ionic Conductivity " << rnemdParameters->cation->getIonName()
                << " = SIGMA_CATION (S/m)\n";
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
                << std::setw(8) << calculateElectrochemicalPotential(
                    individualRegionData[region - 1]->temperature[i],
                    individualRegionData[region - 1]->activity[rnemdParameters->anion->getIonIndex()][i],
                    Phi[runningIndex],
                    rnemdParameters->anion->getIonCharge()) << "\t"
                << std::setw(8) << calculateElectrochemicalPotential(
                    individualRegionData[region - 1]->temperature[i],
                    individualRegionData[region - 1]->activity[rnemdParameters->cation->getIonIndex()][i],
                    Phi[runningIndex],
                    rnemdParameters->cation->getIonCharge()) << "\n";

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
        = Phi.convertQuantity(Conversions::getMolarEnergyConversionFactor("kcal_mol", "eV_part"))
                * charge;

    return diffusionContribution + electricFieldContribution;
}
