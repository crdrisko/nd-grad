// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMDFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/05/2020-11:05:12
// Description: The implementation of charged-RNEMD file parsing

#ifndef CHARGEDRNEMDFILE_HPP
#define CHARGEDRNEMDFILE_HPP

#include "../rnemdFile.hpp"
#include "chargedRNEMDParameters.hpp"

namespace OpenMD::RNEMD::ChargedRNEMD
{
    class ChargedRNEMDFile : public RNEMDFile
    {
    private:
        ChargedRNEMDParametersPtr rnemdParamters { std::make_shared<ChargedRNEMDParameters>() };

        bool hasChargedRNEMDFluxType(std::string_view fluxType) const
        {
            return (fluxType == "Current") || (fluxType == "Single") || (fluxType == "KE+Current");
        }

    public:
        explicit ChargedRNEMDFile(std::string_view FullFileName) : RNEMDFile{FullFileName}
        {
            rnemdParamters->block = this->getRNEMDBlockParameters();
            rnemdParamters->report = this->getRNEMDReportParameters();
            rnemdParamters->inferred = this->getRNEMDInferredParameters();

            if ( !hasChargedRNEMDFluxType(rnemdParamters->block->fluxType) )
                Utilities_API::Errors::printFatalErrorMessage(1,
                    "The supplied flux type does not match one of the Charged-RNEMD flux types");

            for (const auto& selection : rnemdParamters->block->outputSelection)
            {
                if ( Utilities_API::Strings::stringFinder("-", selection) )
                    rnemdParamters->anion = std::make_shared<IonicSpecies>(selection);

                else if ( Utilities_API::Strings::stringFinder("+", selection) )
                    rnemdParamters->cation = std::make_shared<IonicSpecies>(selection);
            }
        }

        ChargedRNEMDParametersPtr getChargedRNEMDParameters() const { return this->rnemdParamters; }
    };

    using ChargedRNEMDFilePtr = std::shared_ptr<ChargedRNEMDFile>;
}

#endif
