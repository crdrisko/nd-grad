// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: shiftXYZ.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/23/2020-17:45:38
// Description: Main ShiftXYZ program, takes a xyz file and region boundary as input and returns a new xyz file

#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

#include <utils-api/errors.hpp>
#include <utils-api/strings.hpp>
#include <cpp-units/physicalQuantities.hpp>

#include "../include/xyzFile.hpp"

using namespace OpenMD::RNEMD;

void printHelpMessageAndExit();

int main(int argc, char* argv[])
{
    std::string inputFileName;
    std::string outputFileName;
    PhysicalQuantities::Length firstRegionIndex;

    Utilities_API::Errors::ErrorMessagePtr errorMessage
        = std::make_shared<Utilities_API::Errors::FatalErrorMessage>("ShiftXYZ", 1);

    int requiredInputCount {2};
    int currentInputCount {};

    for (int option {1}; option < argc; ++option)
    {
        if ( ('-' ==  argv[option][0]) && (std::strlen(argv[option]) == 2) )
        {
            switch (argv[option][1])
            {
            case 'i':
                ++option;

                if ( (argv[option] != NULL) && (Utilities_API::Strings::stringFinder(".xyz", argv[option])) )
                {
                    inputFileName = argv[option];
                    ++currentInputCount;
                }
                break;

            case 'n':
                ++option;

                try
                {
                    firstRegionIndex = PhysicalQuantities::Length(argv[option]);
                    ++currentInputCount;
                }
                catch(const std::exception& e)
                {
                    errorMessage->printErrorMessage(
                        "Exception thrown (and caught), could not convert string to PhysicalQuantities::Length.");
                }
                break;

            case 'o':
                ++option;

                outputFileName = argv[option];
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
        errorMessage->printErrorMessage("Required input is a single valid .xyz file and RNEMD region index.");

    XYZFilePtr xyzFile { std::make_shared<XYZFile>(inputFileName) };

    xyzFile->shiftXYZPositions(firstRegionIndex);
    xyzFile->printOutputToFile(outputFileName);
}


void printHelpMessageAndExit()
{
    std::cout << "\nUSAGE: shiftXYZ [-h] [-i inputFile] [-n regionIndex] [-o outputFile]\n\n"
              << "  -h  Prints help information about the shiftXYZ program.\n\n"
              << "  -i  REQUIRED: The input .xyz file to be shifted.\n"
              << "  -n  REQUIRED: The lower index of the wrapped RNEMD region.\n"
              << "  -o  OPTIONAL: The name of the output .xyz file to write to. Defaults to the\n"
              << "        input file name preceded by 'shifted_'\n\n"
              << "EXAMPLE: shiftXYZ -i single.xyz -n 19.5938\n"
              << std::endl;

    std::exit(0);
}
