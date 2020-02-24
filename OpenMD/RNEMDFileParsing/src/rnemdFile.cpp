// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdFile.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/21/2020-14:16:00
// Description: The implementation of RNEMD file parsing hidden using a pointer to implementation

#include <limits>
#include "../include/rnemdFile.hpp"

using std::vector;
using namespace Utilities_API::PhysicalQuantities;

namespace OpenMD::RNEMD
{
    class RNEMDFile::RNEMDFileImpl : public Utilities_API::Files::TextFile
    {
    private:
        RNEMDDataPtr allDataFromFile { std::make_shared<RNEMDData>() };
        RNEMDParametersPtr rnemdParameters { std::make_shared<RNEMDParameters>() };

        vector< vector<std::string> > superDataVector { this->getSuperDataVector() };
        vector< vector<std::string> > superMetaDataVector { this->getSuperMetaDataVector(" \t\n\";") };

        void setRNEMDData();
        void setRNEMDBlockParameters();
        void setRNEMDReportParameters();
        void setRNEMDInferredParameters();

        int findDataFieldStartLocation(std::string_view dataFieldLabel);
        template<typename T> vector<T> parseDataFromFile(int startIndex = 0);

    public:
        explicit RNEMDFileImpl(const RNEMDFile& rnemdFile);

        RNEMDDataPtr getAllDataFromFile() const { return this->allDataFromFile; }
        RNEMDParametersPtr getRNEMDParameters() const { return this->rnemdParameters; }
    };


    RNEMDFile::RNEMDFileImpl::RNEMDFileImpl(const RNEMDFile& rnemdFile)
        : Utilities_API::Files::TextFile{rnemdFile.fullFileName}
    {
        this->setRNEMDBlockParameters();
        this->setRNEMDReportParameters();
        this->setRNEMDData();
        this->setRNEMDInferredParameters();
    }


    void RNEMDFile::RNEMDFileImpl::setRNEMDBlockParameters()
    {
        rnemdParameters->block->exchangeMethod = superMetaDataVector[2][3];
        rnemdParameters->block->fluxType = superMetaDataVector[3][3];
        rnemdParameters->block->privilegedAxis = superMetaDataVector[4][3];
        rnemdParameters->block->exchangeTime = Time(std::stold(superMetaDataVector[5][3]));

        for (size_t i {4}; i < superMetaDataVector[6].size(); i +=2)
            rnemdParameters->block->objectSelection.push_back(superMetaDataVector[6][i]);

        rnemdParameters->block->selectionA[0] = Length(std::stold(superMetaDataVector[7][6]));
        rnemdParameters->block->selectionA[1] = Length(std::stold(superMetaDataVector[7][10]));

        if (superMetaDataVector[8][4] != "none")
        {
            rnemdParameters->inferred->hasSelectionB = true;
            rnemdParameters->block->selectionB[0] = Length(std::stold(superMetaDataVector[8][6]));
            rnemdParameters->block->selectionB[1] = Length(std::stold(superMetaDataVector[8][10]));
        }

        for (size_t i {4}; i < superMetaDataVector[6].size(); i +=2)
            rnemdParameters->block->outputSelection.push_back(superMetaDataVector[9][i]);

        // The order of outputSelection is reversed before the RNEMD procedure
        std::reverse(rnemdParameters->block->outputSelection.begin(),
            rnemdParameters->block->outputSelection.end());
    }


    void RNEMDFile::RNEMDFileImpl::setRNEMDReportParameters()
    {
        rnemdParameters->report->runningTime = Time(std::stold(superMetaDataVector[13][4]));

        rnemdParameters->report->kineticFlux = MolarEnergyFlux(std::stold(superMetaDataVector[15][3]));
        rnemdParameters->report->kineticTarget = MolarEnergy(std::stold(superMetaDataVector[20][3]));
        rnemdParameters->report->kineticExchange = MolarEnergy(std::stold(superMetaDataVector[24][3]));
        rnemdParameters->report->Jz = MolarEnergyFlux(std::stold(superMetaDataVector[28][3]));

        for (int i {}; i <=2; ++i)
        {
            rnemdParameters->report->momentumFlux[i] = MomentumFlux(std::stold(superMetaDataVector[16][i + 4]));
            rnemdParameters->report->momentumTarget[i] = Momentum(std::stold(superMetaDataVector[21][i + 4]));
            rnemdParameters->report->momentumExchange[i] = Momentum(std::stold(superMetaDataVector[25][i + 4]));
            rnemdParameters->report->JzP[i] = MomentumFlux(std::stold(superMetaDataVector[29][i + 4]));

            rnemdParameters->report->angularMomentumFlux[i] = MomentumFlux(std::stold(superMetaDataVector[17][i + 5]));
            rnemdParameters->report->angularMomentumTarget[i] = Momentum(std::stold(superMetaDataVector[22][i + 5]));
            rnemdParameters->report->angularMomentumExchange[i] = Momentum(std::stold(superMetaDataVector[26][i + 5]));
            rnemdParameters->report->JzL[i] = MomentumFlux(std::stold(superMetaDataVector[30][i + 5]));
        }

        rnemdParameters->report->currentDensity = CurrentDensity(std::stold(superMetaDataVector[18][4]));

        if ( (rnemdParameters->block->fluxType == "Single") || (rnemdParameters->block->fluxType == "Current")
                || (rnemdParameters->block->fluxType == "KE+Current") )
        {
            rnemdParameters->report->Jc_total = CurrentDensity(std::stold(superMetaDataVector[31][5]));
            rnemdParameters->report->Jc_cation = CurrentDensity(std::stold(superMetaDataVector[32][5]));
            rnemdParameters->report->Jc_anion = CurrentDensity(std::stold(superMetaDataVector[33][5]));

            rnemdParameters->report->trialCount = std::stoul(superMetaDataVector[35][3]);
            rnemdParameters->report->failTrialCount = std::stoul(superMetaDataVector[36][3]);

            rnemdParameters->inferred->dataFieldLabelIndex = 38;

            if (rnemdParameters->block->exchangeMethod == "NIVS")
            {
                rnemdParameters->report->failRootCount = std::stoul(superMetaDataVector[37][3]);
                rnemdParameters->inferred->dataFieldLabelIndex = 39;
            }
        }
        else
        {
            rnemdParameters->report->trialCount = std::stoul(superMetaDataVector[32][3]);
            rnemdParameters->report->failTrialCount = std::stoul(superMetaDataVector[33][3]);

            rnemdParameters->inferred->dataFieldLabelIndex = 35;

            if (rnemdParameters->block->exchangeMethod == "NIVS")
            {
                rnemdParameters->report->failRootCount = std::stoul(superMetaDataVector[34][3]);
                rnemdParameters->inferred->dataFieldLabelIndex = 36;
            }
        }
    }


    void RNEMDFile::RNEMDFileImpl::setRNEMDInferredParameters()
    {
        rnemdParameters->inferred->slabWidth
            = rnemdParameters->block->selectionA[1] - rnemdParameters->block->selectionA[0];

        rnemdParameters->inferred->numberOfRegions = (rnemdParameters->block->fluxType == "Single") ? 2 : 4;

        rnemdParameters->inferred->boxSize = allDataFromFile->rnemdAxis[allDataFromFile->rnemdAxis.size() - 1]
            + allDataFromFile->rnemdAxis[0];
    }


    int RNEMDFile::RNEMDFileImpl::findDataFieldStartLocation(std::string_view dataFieldLabel)
    {
        if ( Utilities_API::Strings::stringFinder(dataFieldLabel,
            metaDataVector[rnemdParameters->inferred->dataFieldLabelIndex]) )
            return metaDataVector[rnemdParameters->inferred->dataFieldLabelIndex].find(dataFieldLabel);

        return std::numeric_limits<int>::max();
    }


    template<typename T>
    vector<T> RNEMDFile::RNEMDFileImpl::parseDataFromFile(int startIndex)
    {
        vector<T> PhysicalQuantity;

        for (const auto& vec : superDataVector)
            PhysicalQuantity.push_back( T(std::stold(vec[startIndex])) );

        return PhysicalQuantity;
    }


    void RNEMDFile::RNEMDFileImpl::setRNEMDData()
    {
        vector< std::pair<std::string, int> > locations;

        if (rnemdParameters->block->privilegedAxis != "z")
            allDataFromFile->dataLabels[0] = rnemdParameters->block->privilegedAxis + "(Angstroms)";

        for (const auto& dataLabel : allDataFromFile->dataLabels)
            locations.push_back( std::make_pair(dataLabel, findDataFieldStartLocation(dataLabel)) );

        std::sort( locations.begin(), locations.end(), [](std::pair<std::string, int>& a,
            std::pair<std::string, int>& b) -> bool { return a.second < b.second; } );

        int startIndex {};

        for (const auto& pair : locations)
        {
            if (pair.second != std::numeric_limits<int>::max())
            {
                int index {pair.second - startIndex - 2};

                if (pair.first == allDataFromFile->dataLabels[0])
                    allDataFromFile->rnemdAxis = parseDataFromFile<Length>(index);

                else if (pair.first == allDataFromFile->dataLabels[1])
                    allDataFromFile->radius = parseDataFromFile<Length>(index);

                else if (pair.first == allDataFromFile->dataLabels[2])
                    allDataFromFile->temperature = parseDataFromFile<Temperature>(index);

                else if (pair.first == allDataFromFile->dataLabels[3])
                    for (int i {}; i <= 2 ; ++i)
                        allDataFromFile->velocity[i] = (parseDataFromFile<Velocity>(index + i));

                else if (pair.first == allDataFromFile->dataLabels[4])
                    for (int i {}; i <= 2 ; ++i)
                        allDataFromFile->angularVelocity[i] = (parseDataFromFile<Velocity>(index + i));

                else if (pair.first == allDataFromFile->dataLabels[5])
                    allDataFromFile->density = parseDataFromFile<MassDensity>(index);

                else if (pair.first == allDataFromFile->dataLabels[6])
                {
                    // Only include concentrations for atom types that are actually printed out
                    for (size_t i {}; i < rnemdParameters->block->outputSelection.size(); ++i)
                        if ( Utilities_API::Strings::stringFinder(rnemdParameters->block->outputSelection[i],
                            metaDataVector[rnemdParameters->inferred->dataFieldLabelIndex]) )
                        {
                            startIndex += (1 + rnemdParameters->block->outputSelection[i].length());
                            allDataFromFile->activity.push_back(parseDataFromFile<Concentration>(index + i));
                        }

                    startIndex += 2;
                }

                else if (pair.first == allDataFromFile->dataLabels[7])
                    for (int i {}; i <= 2 ; ++i)
                        allDataFromFile->electricField[i] = (parseDataFromFile<ElectricField>(index + i));

                else if (pair.first == allDataFromFile->dataLabels[8])
                    allDataFromFile->electricPotential = parseDataFromFile<ElectricPotential>(index);

                startIndex += pair.first.length();
            }
        }
    }


    RNEMDFile::RNEMDFile(std::string_view FullFileName) : fullFileName{FullFileName},
        p_Impl{ std::make_unique<RNEMDFileImpl>(*this) } {}

    RNEMDFile::~RNEMDFile() = default;

    RNEMDDataPtr RNEMDFile::getAllDataFromFile() const { return p_Impl->getAllDataFromFile(); }
    RNEMDParametersPtr RNEMDFile::getRNEMDParameters() const { return p_Impl->getRNEMDParameters(); }
    Utilities_API::Files::FileNamePtr RNEMDFile::getFileName() const { return p_Impl->getFileName(); }
}