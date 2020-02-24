// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: shiftXYZ.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/23/2020-17:45:38
// Description: Main ShiftXYZ program, takes a xyz file and region boundary as input and returns a new xyz file

#include "../include/xyzFile.hpp"
#include <utils-api/errors.hpp>
#include <utils-api/strings.hpp>

using namespace Utilities_API;
using namespace OpenMD::RNEMD;

void printHelpMessage();

int main(int argc, char* argv[])
{
    Files::FileNamePtr inputFileName {nullptr};
    PhysicalQuantities::Length firstRegionIndex;
    std::string outputFileName;

    int requiredInputCount {2};
    int currentInputCount {};

    for (int option {1}; option < argc; ++option)
    {
        if ( '-' ==  argv[option][0] )
        {
            switch (argv[option][1])
            {
            case 'i':
                inputFileName = std::make_shared<Files::FileName>(argv[++option]);
                ++currentInputCount;
                break;

            case 'n':
                try
                {
                    firstRegionIndex = PhysicalQuantities::Length(argv[++option]);
                    ++currentInputCount;
                }
                catch(const std::exception& e)
                {
                    Errors::printFatalErrorMessage(1, "Exception thrown, could not convert input to Length.");
                }
                break;

            case 'o':
                outputFileName = argv[++option];
                break;

            case 'h':
                printHelpMessage();
                Errors::printFatalErrorMessage(0, "");
                break;
            default:
                Errors::printFatalErrorMessage(1, "Unknown option passed to the shiftXYZ program.");
                break;
            }
        }
    }

    if ( currentInputCount != requiredInputCount )
        Errors::printFatalErrorMessage(1,
            "ShiftXYZ input requires a single valid .xyz file and a single RNEMD region index.");

    XYZFilePtr xyzFile { std::make_shared<XYZFile>(inputFileName) };

    xyzFile->shiftXYZPositions(firstRegionIndex);
    xyzFile->printOutputToFile(outputFileName);
}

void printHelpMessage()
{
    std::cout << "\nUSAGE: groupSubmit [-h] [-i inputFile] [-n regionIndex] [-o outputFile]\n\n"
              << "  -h  Prints help information about the shiftXYZ program.\n\n"
              << "  -i  REQUIRED: The input .xyz file to be shifted.\n"
              << "  -n  REQUIRED: The lower index of the wrapped RNEMD region.\n"
              << "  -o  OPTIONAL: The name of the output .xyz file to write to. Defaults to the\n"
              << "        input file name preceded by 'shifted_'\n\n"
              << "EXAMPLE: shiftXYZ -i single.xyz -n 19.5938"
              << std::endl;
}
