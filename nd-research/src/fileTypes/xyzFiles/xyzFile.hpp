// Copyright (c) 2019-2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: xyzFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/23/2020-17:45:49
// Description: The XYZFile class used for storing the data and functions associated with an .xyz file

#ifndef ND_RESEARCH_XYZFILE_HPP
#define ND_RESEARCH_XYZFILE_HPP

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <utils-api/files.hpp>

#include "xyzParameters.hpp"
// #include "../../types/molecularEntity.hpp"

namespace ND_Research
{
    class XYZFile : protected Utilities_API::Files::TextFile
    {
    private:
        // std::vector<MolecularEntityPtr> molecularEntities;
        XYZParametersPtr xyzParameters { std::make_shared<XYZParameters>() };

        std::vector<std::vector<std::string>> superDataVector { getSuperDataVector(" \t\n\";") };

        void setNumberOfFrames();
        void parseInputXYZFile(std::size_t currentFrame);

    public:
        explicit XYZFile(std::string_view FullFileName);

        XYZParametersPtr getXYZParameters() const { return xyzParameters; }
        // std::vector<MolecularEntityPtr> getMolecularEntities() const { return molecularEntities; }
        Utilities_API::Files::FileName getFileName() const { return Utilities_API::Files::TextFile::getFileName(); }
    };
}

#endif
