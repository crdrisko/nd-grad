// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: xyzFile.cpp - Version 1.0.0
// Author: cdrisko
// Date: 02/24/2020-07:57:37
// Description: Funtion definitions for the XYZFile class

#include <cstddef>
#include <exception>
#include <string>
#include <string_view>

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/errors.hpp>
#include <utils-api/files.hpp>

#include "xyzFile.hpp"

using namespace PhysicalQuantities;

namespace ND_Research
{
    XYZFile::XYZFile(std::string_view FullFileName) : Utilities_API::Files::TextFile{FullFileName}
    {
        try
        {
            try
            {
                setNumberOfFrames();

                for (std::size_t frame {}; frame < xyzParameters->inferred.numberOfFrames; ++frame)
                    parseInputXYZFile(frame);

                if (xyzParameters->inferred.numberOfFrames > 1)
                    xyzParameters->inferred.timeStep
                        = xyzParameters->frame[1].runTime - xyzParameters->frame[0].runTime;
            }
            catch (const std::exception& except)
            {
                // Toss the exception back up for program termination and a more verbose message
                throw Utilities_API::Errors::InvalidInputException { "ND-Research",
                    "Could not convert a string value from the file into parameter type using: "
                        + std::string{except.what()} };
            }
        }
        catch (const Utilities_API::Errors::Exception& except)
        {
            except.handleErrorWithMessage();
        }
    }


    void XYZFile::setNumberOfFrames()
    {
        /* Assumes the number of atoms is constant in each frame, generally a good assumption
            considering a majority of statistical mechanics ensembles conserve this */
        std::size_t numberOfAtoms { std::stoul(superDataVector[0][0]) };

        xyzParameters->inferred.numberOfFrames = superDataVector.size() / (numberOfAtoms + 2);

        xyzParameters->frame.resize(xyzParameters->inferred.numberOfFrames);
    }


    void XYZFile::parseInputXYZFile(std::size_t currentFrame)
    {
        std::size_t frameStartIndex {};

        if (currentFrame != 0)
            frameStartIndex = currentFrame * (2 + xyzParameters->frame[currentFrame - 1].numberOfAtoms);

        xyzParameters->frame[currentFrame].numberOfAtoms = std::stoul(superDataVector[frameStartIndex][0]);
        xyzParameters->frame[currentFrame].runTime = Time(superDataVector[frameStartIndex + 1][0]);

        int runningIndex {1};

        for (std::size_t i {}; i < 3; ++i)
            for (std::size_t j {}; j < 3; ++j)
                xyzParameters->frame[currentFrame].Hmat[i][j] = Length(superDataVector[frameStartIndex + 1][runningIndex++]);

        // for (std::size_t i {frameStartIndex + 2}; i < xyzParameters->frame[currentFrame].numberOfAtoms + 2; ++i)
        // {
        //     AtomicFactory factory { forceFieldFile };
        //     molecularEntities.push_back( factory.createMolecularEntity(superDataVector[i]) );


        //     xyzParameters->atomLabels.push_back(superDataVector[i][0]);

        //     for (size_t j {}; j < 3; ++j)
        //     xyzParameters->coordinates[j].push_back( Length(superDataVector[i][j + 1]) );
        // }
    }
}
