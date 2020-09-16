// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: chargedRNEMDFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/05/2020-11:05:12
// Description: Parses RNEMD files that classify as ChargedRNEMD files - depends on the supplied flux type

#ifndef ND_RESEARCH_OPENMD_CHARGEDRNEMDFILE_HPP
#define ND_RESEARCH_OPENMD_CHARGEDRNEMDFILE_HPP

#include <memory>
#include <string_view>

#include <utils-api/errors.hpp>
#include <utils-api/strings.hpp>

#include "chargedRNEMDParameters.hpp"
#include "../../RNEMDFileParsing/include/rnemdFile.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class ChargedRNEMDFile : public RNEMDFile
    {
    private:
        ChargedRNEMDParametersPtr rnemdParameters { std::make_shared<ChargedRNEMDParameters>() };

        Utilities_API::Errors::ErrorMessagePtr errorMessage
            = std::make_shared<Utilities_API::Errors::FatalErrorMessage>("ChargedRNEMD", 2);

        bool hasChargedRNEMDFluxType(std::string_view fluxType) const
        {
            return (fluxType == "Current") || (fluxType == "Single") || (fluxType == "KE+Current");
        }

    public:
        explicit ChargedRNEMDFile(std::string_view FullFileName) : RNEMDFile{FullFileName}
        {
            rnemdParameters->block = getRNEMDParameters()->block;
            rnemdParameters->report = getRNEMDParameters()->report;
            rnemdParameters->inferred = getRNEMDParameters()->inferred;

            if ( !hasChargedRNEMDFluxType(rnemdParameters->block->fluxType) )
                errorMessage->printErrorMessage(
                    "The supplied flux type does not match one of the ChargedRNEMD flux types.");

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
        }

        ChargedRNEMDParametersPtr getChargedRNEMDParameters() const { return rnemdParameters; }
    };

    using ChargedRNEMDFilePtr = std::shared_ptr<ChargedRNEMDFile>;
}

#endif
