// Copyright (c) 2020-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: rnemdFile.hpp
// Author: crdrisko
// Date: 11/22/2022-08:32:55
// Description:

#ifndef DRYCHEM_COMMON_UTILITIES_SRC_APPLICATIONS_RNEMD_RNEMDFILE_HPP
#define DRYCHEM_COMMON_UTILITIES_SRC_APPLICATIONS_RNEMD_RNEMDFILE_HPP

#include <algorithm>
#include <string>

#include <common-utils/files.hpp>

#include "rnemdParameters.hpp"

namespace ND_Research
{
    class RNEMDFile
    {
    private:
        RNEMDData data_ {};
        RNEMDData errors_ {};
        RNEMDParameters params_ {};
        std::string fileName_ {};

        RNEMDData parseDataFields(const std::string& dataContents);
        std::string removeQuotes(const std::string& str) const;
        void determineActivity(const std::string& row);
        std::string generateSelectionScript(const std::vector<std::string>& selectionScript) const;

        template<typename T>
        std::string generateVector3Ds(const DryChem::Vector3D<T>& vector2Print) const;

    public:
        explicit RNEMDFile(const std::string& fileName) : fileName_ {fileName}
        {
            DryChem::FileParser parser {fileName};

            parser.parseDataFile(*this);
        }

        RNEMDFile(const RNEMDData& data, const RNEMDData& errors, const RNEMDParameters& params)
            : data_ {data}, errors_ {errors}, params_ {params}
        {
        }

        void operator()(const std::string& fileContents_);

        int determineRegionBounds(const CppUnits::Length& wrappedZCoords) const;

        RNEMDData getRNEMDData() const { return data_; }
        RNEMDData getRNEMDErrors() const { return errors_; }
        RNEMDParameters getRNEMDParameters() const { return params_; }

        void writeRNEMDFile(const std::string& fileName) const;
    };
}   // namespace ND_Research

#endif
