// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/11/2020-12:42:57
// Description: Main ChargedRNEMD program, takes a rnemd file as input and returns the analysis in an ecp file

#include <cstring>
#include "../include/methodFactory.hpp"

using namespace Utilities_API;
using namespace OpenMD::RNEMD::ChargedRNEMD;

void printHelpMessageAndExit();

int main(int argc, char* argv[])
{
    Files::FileNamePtr inputFileName;

    int requiredInputCount {1};
    int currentInputCount {};

    for (int option {1}; option < argc; ++option)
    {
        if ( ('-' ==  argv[option][0]) && (std::strlen(argv[option]) == 2) )
        {
            switch (argv[option][1])
            {
            case 'i':
                ++option;

                if ( (argv[option] != NULL) && (Strings::stringFinder(".rnemd", argv[option])) )
                {
                    inputFileName = std::make_shared<Files::FileName>(argv[option]);
                    ++currentInputCount;
                }
                break;

            case 'h':
                printHelpMessageAndExit();
                break;

            default:
                Errors::printFatalErrorMessage(1, "Unknown option passed to the shiftXYZ program.");
                break;
            }
        }
    }

    if ( currentInputCount != requiredInputCount )
        Errors::printFatalErrorMessage(1, "ChargedRNEMD input requires a single valid .rnemd file.");

    MethodFactory methodFactory {inputFileName};
    ChargedRNEMDAnalysisMethodPtr rnemdAnalysisMethod { methodFactory.createMethod() };

    rnemdAnalysisMethod->process();
    rnemdAnalysisMethod->printOutputToFile();
}


void printHelpMessageAndExit()
{
    std::cout << "\nUSAGE: chargedRNEMD [-h] [-i inputFile]\n\n"
              << "  -h  Prints help information about the chargedRNEMD program.\n\n"
              << "  -i  REQUIRED: The input .rnemd file to be analyzed.\n\n"
              << "EXAMPLE: chargedRNEMD -i single.rnemd\n"
              << std::endl;

    std::exit(0);
}
