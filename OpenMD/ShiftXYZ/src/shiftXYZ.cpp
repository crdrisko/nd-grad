// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: shiftXYZ.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/23/2020-17:45:38
// Description: Main ShiftXYZ program, takes a xyz file and region boundary as input and returns a new xyz file

#include "../include/xyzFile.hpp"
#include <utils-api/errors.hpp>

using namespace Utilities_API;
using namespace OpenMD::RNEMD;

void printHelpMessageAndExit();

int main(int argc, char* argv[])
{
    Files::FileNamePtr inputFileName;
    PhysicalQuantities::Length firstRegionIndex;
    std::string outputFileName;

    int requiredInputCount {2};
    int currentInputCount {};

    for (int option {1}; option < argc; ++option)
    {
        if ( ('-' ==  argv[option][0]) && (strlen(argv[option]) == 2) )
        {
            switch (argv[option][1])
            {
            case 'i':
                ++option;

                if ( (argv[option] != NULL) && (Strings::stringFinder(".xyz", argv[option])) )
                {
                    inputFileName = std::make_shared<Files::FileName>(argv[option]);
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
                    Errors::printFatalErrorMessage(1,
                        "Exception thrown (and caught), could not convert string to Length.");
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
                Errors::printFatalErrorMessage(1, "Unknown option passed to the shiftXYZ program.");
                break;
            }
        }
    }

    if ( currentInputCount != requiredInputCount )
        Errors::printFatalErrorMessage(1,
            "ShiftXYZ input requires a single valid .xyz file and RNEMD region index.");

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
