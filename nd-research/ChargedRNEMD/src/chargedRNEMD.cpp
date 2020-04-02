// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: chargedRNEMD.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/11/2020-12:42:57
// Description: Main ChargedRNEMD program, takes a rnemd file as input and returns the analysis in an ecp file

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#include <utils-api/errors.hpp>
#include <utils-api/strings.hpp>

#include "../include/methodFactory.hpp"

using namespace OpenMD::RNEMD::ChargedRNEMD;

void printHelpMessageAndExit();

int main(int argc, char* argv[])
{
    std::string inputFileName;

    bool doMethodOptimization {false};
    std::string methodOptimizationOutputFileName;

    Utilities_API::Errors::ErrorMessagePtr errorMessage
        = std::make_shared<Utilities_API::Errors::FatalErrorMessage>("ChargedRNEMD", 3);

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

                if ( (argv[option] != NULL) && (Utilities_API::Strings::stringFinder(".rnemd", argv[option])) )
                {
                    inputFileName = argv[option];
                    ++currentInputCount;
                }
                break;
            case 'o':
                ++option;

                if (argv[option] != NULL)
                {
                    doMethodOptimization = true;
                    methodOptimizationOutputFileName = argv[option];
                }
                else
                    errorMessage->printErrorMessage("The -o option requires a fileName for output.");
                break;
            case 'h':
                printHelpMessageAndExit();
                break;
            default:
                errorMessage->printErrorMessage("Unknown option passed to the program.");
                break;
            }
        }
    }

    if (currentInputCount != requiredInputCount)
        errorMessage->printErrorMessage("Required input is a single valid .rnemd file.");

    MethodFactory methodFactory {inputFileName};
    ChargedRNEMDAnalysisMethodPtr rnemdAnalysisMethod { methodFactory.createMethod() };

    rnemdAnalysisMethod->process();
    rnemdAnalysisMethod->printOutputToFile();

    if (doMethodOptimization)
        rnemdAnalysisMethod->printOptimizationAnalysisToFile(methodOptimizationOutputFileName);
}


void printHelpMessageAndExit()
{
    std::cout << "\nUSAGE: chargedRNEMD [-h] [-i inputFile] [-o outputFile]\n\n"
              << "  -h  Prints help information about the chargedRNEMD program.\n\n"
              << "  -i  REQUIRED: The input .rnemd file to be analyzed.\n"
              << "  -o  OPTIONAL: The output file for easy method optimization analysis.\n\n"
              << "EXAMPLE: chargedRNEMD -i single.rnemd -o single.opt\n"
              << std::endl;

    std::exit(0);
}
