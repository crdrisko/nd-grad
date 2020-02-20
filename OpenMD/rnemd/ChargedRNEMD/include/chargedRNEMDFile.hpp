// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/05/2020-11:05:12
// Description: Parses RNEMD files that classify as ChargedRNEMD files - depends on the supplied flux type

#ifndef CHARGEDRNEMDFILE_HPP
#define CHARGEDRNEMDFILE_HPP

#include <utilities-api/strings.hpp>
#include "chargedRNEMDParameters.hpp"
#include "../../RNEMDFileParsing/include/rnemdFile.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class ChargedRNEMDFile : public RNEMDFile
    {
    private:
        ChargedRNEMDParametersPtr rnemdParameters { std::make_shared<ChargedRNEMDParameters>() };
        std::vector<RNEMDDataPtr> individualRegionData;

        bool hasChargedRNEMDFluxType(std::string_view fluxType) const
        {
            return (fluxType == "Current") || (fluxType == "Single") || (fluxType == "KE+Current");
        }

    public:
        explicit ChargedRNEMDFile(std::string_view FullFileName) : RNEMDFile{FullFileName}
        {
            rnemdParameters->block = this->getRNEMDBlockParameters();
            rnemdParameters->report = this->getRNEMDReportParameters();
            rnemdParameters->inferred = this->getRNEMDInferredParameters();

            if ( !hasChargedRNEMDFluxType(rnemdParameters->block->fluxType) )
                Utilities_API::Errors::printFatalErrorMessage(1,
                    "The supplied flux type does not match one of the Charged-RNEMD flux types");

            int ionicSpeciesCount {};

            for (const auto& selection : rnemdParameters->block->outputSelection)
            {
                if ( (Utilities_API::Strings::stringFinder("-", selection))
                  || (Utilities_API::Strings::stringFinder("+", selection)) )
                    rnemdParameters->ionicSpecies.push_back(std::make_shared<IonicSpecies>(selection,
                        ionicSpeciesCount));

                else
                    continue;

                ++ionicSpeciesCount;
            }

            std::vector<RNEMDRegionPtr> rnemdRegionData { this->getRNEMDRegions() };

            for (int region {1}; region <= rnemdParameters->inferred->numberOfRegions; ++region)
            {
                individualRegionData.push_back(rnemdRegionData[region - 1]->getRegionSpecificData());

                if (region == 1)
                    rnemdRegionData[0]->makeFirstRegionContinuous(rnemdParameters->inferred->boxSize);
            }
        }

        ChargedRNEMDParametersPtr getChargedRNEMDParameters() const { return this->rnemdParameters; }
        std::vector<RNEMDDataPtr> getIndividualRegionData() const { return this->individualRegionData; }
    };

    using ChargedRNEMDFilePtr = std::shared_ptr<ChargedRNEMDFile>;
}

#endif
