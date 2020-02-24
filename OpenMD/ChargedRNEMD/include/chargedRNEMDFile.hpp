// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/05/2020-11:05:12
// Description: Parses RNEMD files that classify as ChargedRNEMD files - depends on the supplied flux type

#ifndef CHARGEDRNEMDFILE_HPP
#define CHARGEDRNEMDFILE_HPP

#include <utils-api/strings.hpp>
#include "chargedRNEMDParameters.hpp"
#include "../../RNEMDFileParsing/include/rnemdFile.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class ChargedRNEMDFile : public RNEMDFile
    {
    private:
        ChargedRNEMDParametersPtr rnemdParameters { std::make_shared<ChargedRNEMDParameters>() };

        bool hasChargedRNEMDFluxType(std::string_view fluxType) const
        {
            return (fluxType == "Current") || (fluxType == "Single") || (fluxType == "KE+Current");
        }

    public:
        explicit ChargedRNEMDFile(std::string_view FullFileName) : RNEMDFile{FullFileName}
        {
            rnemdParameters->block = this->getRNEMDParameters()->block;
            rnemdParameters->report = this->getRNEMDParameters()->report;
            rnemdParameters->inferred = this->getRNEMDParameters()->inferred;

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
        }

        ChargedRNEMDParametersPtr getChargedRNEMDParameters() const { return this->rnemdParameters; }
    };

    using ChargedRNEMDFilePtr = std::shared_ptr<ChargedRNEMDFile>;
}

#endif
