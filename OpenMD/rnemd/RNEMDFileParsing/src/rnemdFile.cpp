// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdFile.cpp - Version 1.0.0
// Author: cdrisko
// Date: 01/21/2020-14:16:00
// Description: The implementation of RNEMD file parsing hidden using a pointer to implementation

#include <limits>
#include <utility>
#include <utilities-api/files.hpp>
#include "../include/rnemdFile.hpp"

using namespace Utilities_API::PhysicalQuantities;

namespace OpenMD::RNEMD
{
    class RNEMDFile::RNEMDFileImpl : public Utilities_API::Files::TextFile
    {
    private:
        RNEMDDataPtr allDataFromFile { std::make_shared<RNEMDData>() };
        std::vector<RNEMDRegionPtr> rnemdRegionData;

        RNEMDBlockParametersPtr rnemdBlock { std::make_shared<RNEMDBlockParameters>() };
        RNEMDReportParametersPtr rnemdReport { std::make_shared<RNEMDReportParameters>() };
        RNEMDInferredParametersPtr rnemdInferred { std::make_shared<RNEMDInferredParameters>() };

        std::vector< std::vector<std::string> > superDataVector { getSuperDataVector() };
        std::vector< std::vector<std::string> > superMetaDataVector { getSuperMetaDataVector(" \t\n\";") };

        void setRNEMDData();
        void setRNEMDRegions();
        void setRNEMDBlockParameters();
        void setRNEMDReportParameters();
        void setRNEMDInferredParameters();

        std::vector<Length> parseWrappedZSelections();
        int findDataFieldStartLocation(std::string_view dataFieldLabel);
        template<typename T> std::vector<T> parseDataFromFile(int startIndex = 0);

        Length convertWrappedZ_to_z(Length wrapped_z) const
        {
            return (rnemdInferred->boxSize / 2.0_) + wrapped_z;
        }

        int boundFinder(const Length& regionBound) const
        {
            /* Need to account for the (binNumber * 0.5) * (boxSize / numberOfBins) issue */
            return std::lower_bound(allDataFromFile->rnemdAxis.begin(), allDataFromFile->rnemdAxis.end(),
                regionBound) - allDataFromFile->rnemdAxis.begin();
        }

    public:
        explicit RNEMDFileImpl(const RNEMDFile& rnemdFile);

        RNEMDDataPtr getAllDataFromFile() const{ return this->allDataFromFile; }
        std::vector<RNEMDRegionPtr> getRNEMDRegions() const { return this->rnemdRegionData; }
        RNEMDBlockParametersPtr getRNEMDBlockParameters() const { return this->rnemdBlock; }
        RNEMDReportParametersPtr getRNEMDReportParameters() const { return this->rnemdReport; }
        RNEMDInferredParametersPtr getRNEMDInferredParameters() const { return this->rnemdInferred; }
    };

    RNEMDFile::RNEMDFileImpl::RNEMDFileImpl(const RNEMDFile& rnemdFile)
        : Utilities_API::Files::TextFile{rnemdFile.fullFileName}
    {
        this->setRNEMDBlockParameters();
        this->setRNEMDReportParameters();
        this->setRNEMDData();
        this->setRNEMDInferredParameters();
        this->setRNEMDRegions();
    }

    void RNEMDFile::RNEMDFileImpl::setRNEMDBlockParameters()
    {
        rnemdBlock->exchangeMethod = superMetaDataVector[2][3];
        rnemdBlock->fluxType = superMetaDataVector[3][3];
        rnemdBlock->privilegedAxis = superMetaDataVector[4][3];
        rnemdBlock->exchangeTime = Time(std::stold(superMetaDataVector[5][3]));

        for (size_t i {4}; i < superMetaDataVector[6].size(); i +=2)
            rnemdBlock->objectSelection.push_back(superMetaDataVector[6][i]);

        rnemdBlock->selectionA[0] = Length(std::stold(superMetaDataVector[7][6]));
        rnemdBlock->selectionA[1] = Length(std::stold(superMetaDataVector[7][10]));

        if (superMetaDataVector[8][4] != "none")
        {
            rnemdInferred->hasSelectionB = true;
            rnemdBlock->selectionB[0] = Length(std::stold(superMetaDataVector[8][6]));
            rnemdBlock->selectionB[1] = Length(std::stold(superMetaDataVector[8][10]));
        }

        for (size_t i {4}; i < superMetaDataVector[6].size(); i +=2)
            rnemdBlock->outputSelection.push_back(superMetaDataVector[9][i]);

        // The order of outputSelection is reversed before the RNEMD procedure
        std::reverse(rnemdBlock->outputSelection.begin(), rnemdBlock->outputSelection.end());
    }

    void RNEMDFile::RNEMDFileImpl::setRNEMDReportParameters()
    {
        rnemdReport->runningTime = Time(std::stold(superMetaDataVector[13][4]));

        rnemdReport->kineticFlux = MolarEnergyFlux(std::stold(superMetaDataVector[15][3]));
        rnemdReport->kineticTarget = MolarEnergy(std::stold(superMetaDataVector[20][3]));
        rnemdReport->kineticExchange = MolarEnergy(std::stold(superMetaDataVector[24][3]));
        rnemdReport->Jz = MolarEnergyFlux(std::stold(superMetaDataVector[28][3]));

        for (int i {}; i <=2; ++i)
        {
            rnemdReport->momentumFlux[i] = MomentumFlux(std::stold(superMetaDataVector[16][i + 4]));
            rnemdReport->momentumTarget[i] = Momentum(std::stold(superMetaDataVector[21][i + 4]));
            rnemdReport->momentumExchange[i] = Momentum(std::stold(superMetaDataVector[25][i + 4]));
            rnemdReport->JzP[i] = MomentumFlux(std::stold(superMetaDataVector[29][i + 4]));

            rnemdReport->angularMomentumFlux[i] = MomentumFlux(std::stold(superMetaDataVector[17][i + 5]));
            rnemdReport->angularMomentumTarget[i] = Momentum(std::stold(superMetaDataVector[22][i + 5]));
            rnemdReport->angularMomentumExchange[i] = Momentum(std::stold(superMetaDataVector[26][i + 5]));
            rnemdReport->JzL[i] = MomentumFlux(std::stold(superMetaDataVector[30][i + 5]));
        }

        rnemdReport->currentDensity = CurrentDensity(std::stold(superMetaDataVector[18][4]));

        if ( (rnemdBlock->fluxType == "Single") || (rnemdBlock->fluxType == "Current")
                || (rnemdBlock->fluxType == "KE+Current") )
        {
            rnemdReport->Jc_total = CurrentDensity(std::stold(superMetaDataVector[31][5]));
            rnemdReport->Jc_cation = CurrentDensity(std::stold(superMetaDataVector[32][5]));
            rnemdReport->Jc_anion = CurrentDensity(std::stold(superMetaDataVector[33][5]));

            rnemdReport->trialCount = std::stoul(superMetaDataVector[35][3]);
            rnemdReport->failTrialCount = std::stoul(superMetaDataVector[36][3]);

            rnemdInferred->dataFieldLabelIndex = 38;

            if (rnemdBlock->exchangeMethod == "NIVS")
            {
                rnemdReport->failRootCount = std::stoul(superMetaDataVector[37][3]);
                rnemdInferred->dataFieldLabelIndex = 39;
            }
        }
        else
        {
            rnemdReport->trialCount = std::stoul(superMetaDataVector[32][3]);
            rnemdReport->failTrialCount = std::stoul(superMetaDataVector[33][3]);

            rnemdInferred->dataFieldLabelIndex = 35;

            if (rnemdBlock->exchangeMethod == "NIVS")
            {
                rnemdReport->failRootCount = std::stoul(superMetaDataVector[34][3]);
                rnemdInferred->dataFieldLabelIndex = 36;
            }
        }
    }

    void RNEMDFile::RNEMDFileImpl::setRNEMDInferredParameters()
    {
        rnemdInferred->slabWidth = rnemdBlock->selectionA[1] - rnemdBlock->selectionA[0];
        rnemdInferred->numberOfRegions = (rnemdBlock->fluxType == "Single") ? 2 : 4;
        rnemdInferred->boxSize = allDataFromFile->rnemdAxis[allDataFromFile->rnemdAxis.size() - 1]
            + allDataFromFile->rnemdAxis[0];
    }

    int RNEMDFile::RNEMDFileImpl::findDataFieldStartLocation(std::string_view dataFieldLabel)
    {
        if ( Utilities_API::Strings::stringFinder(dataFieldLabel,
            metaDataVector[rnemdInferred->dataFieldLabelIndex]) )
            return metaDataVector[rnemdInferred->dataFieldLabelIndex].find(dataFieldLabel);

        return std::numeric_limits<int>::max();
    }

    template<typename T>
    std::vector<T> RNEMDFile::RNEMDFileImpl::parseDataFromFile(int startIndex)
    {
        std::vector<T> PhysicalQuantity;

        for (const auto& vec : superDataVector)
            PhysicalQuantity.push_back( T(std::stold(vec[startIndex])) );

        return PhysicalQuantity;
    }

    void RNEMDFile::RNEMDFileImpl::setRNEMDData()
    {
        std::vector< std::pair<std::string, int> > locations;

        if (rnemdBlock->privilegedAxis != "z")
            allDataFromFile->dataLabels[0] = rnemdBlock->privilegedAxis + "(Angstroms)";

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
                    for (int i {}; i < rnemdBlock->outputSelection.size(); ++i)
                        if ( Utilities_API::Strings::stringFinder(rnemdBlock->outputSelection[i],
                            metaDataVector[rnemdInferred->dataFieldLabelIndex]) )
                        {
                            startIndex += (1 + rnemdBlock->outputSelection[i].length());
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

    std::vector<Length> RNEMDFile::RNEMDFileImpl::parseWrappedZSelections()
    {
        std::vector<Length> regionBounds;

        regionBounds.push_back(0.0_Ang);

        if (rnemdInferred->hasSelectionB)
            regionBounds.push_back(convertWrappedZ_to_z(rnemdBlock->selectionB[1]));

        regionBounds.push_back(convertWrappedZ_to_z(rnemdBlock->selectionA[0]));
        regionBounds.push_back(convertWrappedZ_to_z(rnemdBlock->selectionA[1]));

        if (rnemdInferred->hasSelectionB)
            regionBounds.push_back(convertWrappedZ_to_z(rnemdBlock->selectionB[0]));

        regionBounds.push_back(rnemdInferred->boxSize);

        return regionBounds;
    }

    void RNEMDFile::RNEMDFileImpl::setRNEMDRegions()
    {
        std::vector<Length> regionBounds { this->parseWrappedZSelections() };

        for (int region {1}; region <= rnemdInferred->numberOfRegions; ++region)
        {
            int lowerBoundOfRegion {boundFinder(regionBounds[region - 1])};
            int upperBoundOfRegion {boundFinder(regionBounds[region])};

            int lowerBoundOfFirstRegion {};
            int upperBoundOfFirstRegion {};

            if (region == 1)
            {
                lowerBoundOfFirstRegion = lowerBoundOfRegion;
                upperBoundOfFirstRegion = upperBoundOfRegion;

                lowerBoundOfRegion = boundFinder(regionBounds[rnemdInferred->numberOfRegions]);
                upperBoundOfRegion = boundFinder(regionBounds[rnemdInferred->numberOfRegions + 1]);
            }

            this->rnemdRegionData.push_back(std::make_shared<RNEMDRegion>(allDataFromFile,
                lowerBoundOfRegion, upperBoundOfRegion, lowerBoundOfFirstRegion, upperBoundOfFirstRegion));
        }
    }


    // Definition of the RNEMDFile public interface
    RNEMDFile::RNEMDFile(std::string_view FullFileName) : fullFileName{FullFileName},
        p_Impl{ std::make_unique<RNEMDFileImpl>(*this) } {}

    RNEMDFile::~RNEMDFile() = default;

    RNEMDDataPtr RNEMDFile::getAllDataFromFile() const
    {
        return p_Impl->getAllDataFromFile();
    }

    std::vector<RNEMDRegionPtr> RNEMDFile::getRNEMDRegions() const
    {
        return p_Impl->getRNEMDRegions();
    }

    RNEMDBlockParametersPtr RNEMDFile::getRNEMDBlockParameters() const
    {
        return p_Impl->getRNEMDBlockParameters();
    }

    RNEMDReportParametersPtr RNEMDFile::getRNEMDReportParameters() const
    {
        return p_Impl->getRNEMDReportParameters();
    }

    RNEMDInferredParametersPtr RNEMDFile::getRNEMDInferredParameters() const
    {
        return p_Impl->getRNEMDInferredParameters();
    }
}
