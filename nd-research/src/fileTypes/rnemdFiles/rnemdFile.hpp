// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/20/2020-15:43:58
// Description: The RNEMDFile class used for storing the data and functions associated with an .rnemd file

#ifndef ND_RESEARCH_RNEMDFILE_HPP
#define ND_RESEARCH_RNEMDFILE_HPP

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <utils-api/files.hpp>

#include "rnemdParameters.hpp"

namespace ND_Research
{
    class RNEMDFile : public Utilities_API::Files::TextFile
    {
    private:
        RNEMDDataPtr rnemdData { std::make_shared<RNEMDData>() };
        RNEMDParametersPtr rnemdParameters { std::make_shared<RNEMDParameters>() };

        std::vector< std::vector<std::string> > superMetaDataVector { getSuperMetaDataVector(" \t\n\";") };

        void setRNEMDBlockParameters(std::size_t& row);
        void setRNEMDReportParameters(std::size_t& row);
        void setRNEMDData();
        void setRNEMDInferredParameters();

    public:
        explicit RNEMDFile(std::string_view FullFileName);

        auto getRNEMDData() const { return rnemdData; }
        auto getRNEMDParameters() const { return rnemdParameters; }
        auto getFileName() const { return Utilities_API::Files::TextFile::getFileName(); }
    };
}

#endif
