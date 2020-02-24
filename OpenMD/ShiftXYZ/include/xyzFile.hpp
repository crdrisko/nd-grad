// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: xyzFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/23/2020-17:45:49
// Description: The XYZFile class used for storing the data and functions associated with a .xyz file

#ifndef XYZFILE_HPP
#define XYZFILE_HPP

#include <array>
#include <utils-api/files.hpp>
#include <utils-api/physicalQuantities.hpp>

namespace OpenMD::RNEMD
{
    struct XYZParameters
    {
        int numberOfAtoms;
        Utilities_API::PhysicalQuantities::Time runTime;

        std::array<std::array<Utilities_API::PhysicalQuantities::Length, 3>, 3> Hmat;

        std::vector<std::string> atomLabels;
        std::array<std::vector<Utilities_API::PhysicalQuantities::Length>, 3> coordinates;
    };

    using XYZParametersPtr = std::shared_ptr<XYZParameters>;


    class XYZFile : public Utilities_API::Files::TextFile
    {
    private:
        XYZParametersPtr xyzParameters { std::make_shared<XYZParameters>() };
        std::vector< std::vector<std::string> > superDataVector { this->getSuperDataVector(" \t\n\";") };

        void parseInputXYZFile();

    public:
        XYZFile(std::string_view FullFileName)
            : Utilities_API::Files::TextFile{FullFileName} { this->parseInputXYZFile(); }

        XYZFile(Utilities_API::Files::FileNamePtr FileName) : XYZFile{ FileName->getFullFileName() } {}

        void shiftXYZPositions(const Utilities_API::PhysicalQuantities::Length& firstRegionBound)
        {
            for (auto& z : xyzParameters->coordinates[2])
                if (z > firstRegionBound)
                    z -= xyzParameters->Hmat[2][2];
        }

        void printOutputToFile(std::string outputFileName = "") const;
        XYZParametersPtr getXYZParameters() const { return this->xyzParameters; }
    };

    using XYZFilePtr = std::shared_ptr<XYZFile>;
}

#endif
