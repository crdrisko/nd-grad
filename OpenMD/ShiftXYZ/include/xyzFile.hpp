// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: xyzFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/23/2020-17:45:49
// Description: The XYZFile class used for storing the data and functions associated with a .xyz file

#ifndef ND_RESEARCH_OPENMD_XYZFILE_HPP
#define ND_RESEARCH_OPENMD_XYZFILE_HPP

#include <array>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <cpp-units/physicalQuantities.hpp>
#include <utils-api/files.hpp>

namespace OpenMD::RNEMD
{
    struct XYZParameters
    {
        int numberOfAtoms;
        PhysicalQuantities::Time runTime;

        std::array<std::array<PhysicalQuantities::Length, 3>, 3> Hmat;

        std::vector<std::string> atomLabels;
        std::array<std::vector<PhysicalQuantities::Length>, 3> coordinates;

        // std::multimap<std::string_view, std::array<PhysicalQuantities::Length, 3> > atomCoordinates;
    };

    using XYZParametersPtr = std::shared_ptr<XYZParameters>;


    class XYZFile : public Utilities_API::Files::TextFile
    {
    private:
        XYZParametersPtr xyzParameters { std::make_shared<XYZParameters>() };
        std::vector< std::vector<std::string> > superDataVector { getSuperDataVector(" \t\n\";") };

        void parseInputXYZFile();

    public:
        explicit XYZFile(std::string_view FullFileName) : Utilities_API::Files::TextFile{FullFileName}
        {
            parseInputXYZFile();
        }

        void shiftXYZPositions(const PhysicalQuantities::Length& firstRegionBound)
        {
            for (auto& z : xyzParameters->coordinates[2])
                if (z > firstRegionBound)
                    z -= xyzParameters->Hmat[2][2];
        }

        // void shiftXYZPositions(const PhysicalQuantities::Length& firstRegionBound)
        // {
        //     const PhysicalQuantities::Length SPCE_bondLength = 1.0_Ang;

        //     for (auto& [atomLabel, coordinates] : xyzParameters->atomCoordinates)
        //         if (coordinates[2] > firstRegionBound)
        //             coordinates[2] -= xyzParameters->Hmat[2][2];
        // }

        void printOutputToFile(std::string outputFileName = "") const;
        XYZParametersPtr getXYZParameters() const { return xyzParameters; }
    };

    using XYZFilePtr = std::shared_ptr<XYZFile>;
}

#endif
