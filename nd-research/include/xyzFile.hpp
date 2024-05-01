// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: xyzFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/23/2020-17:45:49
// Description: The XYZFile class used for storing the data and functions associated with an .xyz file

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_XYZFILE_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_XYZFILE_HPP

#include <cstddef>
#include <filesystem>
#include <vector>

#include "xyzParameters.hpp"

namespace ND_Research
{
    class XYZFile
    {
    private:
        XYZParameters params;
        std::vector<std::vector<XYZData>> data;
        std::filesystem::path fileName;

        bool hasNextFrame(const std::vector<std::string>& rows_);
        void parseInputXYZFile(const std::vector<std::string>& rows_, std::size_t currentFrame_);

    public:
        explicit XYZFile(const std::filesystem::path& fileName_);

        void printOutputFile() const;
    };
}   // namespace ND_Research

#endif
