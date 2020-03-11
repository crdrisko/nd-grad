// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: xyzFile.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/24/2020-07:57:37
// Description: Funtion definitions for the XYZFile class

#include <fstream>
#include <iomanip>
#include <string>

#include <cpp-units/physicalQuantities.hpp>

#include "../include/xyzFile.hpp"

using namespace PhysicalQuantities;

namespace OpenMD::RNEMD
{
    void XYZFile::parseInputXYZFile()
    {
        xyzParameters->numberOfAtoms = std::stoi(superDataVector[0][0]);
        xyzParameters->runTime = Time(superDataVector[1][0]);

        int runningIndex {1};

        for (size_t i {}; i < 3; ++i)
            for (size_t j {}; j < 3; ++j)
                xyzParameters->Hmat[i][j] = Length(superDataVector[1][runningIndex++]);

        for (size_t i {2}; i < superDataVector.size(); ++i)
        {
            xyzParameters->atomLabels.push_back(superDataVector[i][0]);

            for (size_t j {}; j < 3; ++j)
                xyzParameters->coordinates[j].push_back( Length(superDataVector[i][j + 1]) );
        }
    }

    void XYZFile::printOutputToFile(std::string outputFileName) const
    {
        if ( outputFileName.empty() )
        {
            outputFileName = getFileName().getFullFileName();
            outputFileName.insert(outputFileName.find_last_of("/") + 1, "shifted_");
        }

        std::ofstream outputFile;
        outputFile.open(outputFileName);

        outputFile << std::setprecision(8) << std::fixed;

        outputFile << xyzParameters->numberOfAtoms << "\n";
        outputFile << xyzParameters->runTime;

        for (const auto& firstCoordinate : xyzParameters->Hmat)
        {
            outputFile << ";";

            for (const auto& secondCoordinate : firstCoordinate)
                outputFile << std::setw(15) << secondCoordinate;
        }

        for (size_t i {}; i < xyzParameters->atomLabels.size(); ++i)
        {
            outputFile << "\n" << xyzParameters->atomLabels[i];

            for (size_t j {}; j < 3; ++j)
                outputFile << std::setw(15) << xyzParameters->coordinates[j][i];
        }

        outputFile << std::endl;
    }
}
