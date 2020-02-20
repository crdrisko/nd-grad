// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/11/2020-12:42:57
// Description: Main ChargedRNEMD program, takes a rnemd file as input and returns the analysis in an ecp file

#include "../include/methodFactory.hpp"

using namespace Utilities_API;
using namespace OpenMD::RNEMD::ChargedRNEMD;

int main(int argc, char* argv[])
{
    Files::FileNamePtr fileName {nullptr};

    for (int option {1}; option < argc; ++option)
        if ( Strings::stringFinder(".rnemd", argv[option]) )
            fileName = std::make_shared<Files::FileName>(argv[option]);

    if (!fileName)
        Errors::printFatalErrorMessage(1, "ChargedRNEMD input requires a valid .rnemd file.");

    MethodFactory methodFactory {fileName};
    ChargedRNEMDAnalysisMethodPtr rnemdAnalysisMethod { methodFactory.createMethod() };

    rnemdAnalysisMethod->process();
}
