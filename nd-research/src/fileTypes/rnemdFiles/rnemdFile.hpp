// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/20/2020-15:43:58
// Description: The RNEMDFile class used for storing the data and functions associated with an .rnemd file

#ifndef ND_RESEARCH_RNEMDFILE_HPP
#define ND_RESEARCH_RNEMDFILE_HPP

#include <memory>
#include <string>
#include <string_view>

#include <utils-api/files.hpp>

#include "rnemdParameters.hpp"

namespace ND_Research
{
    class RNEMDFile : public Utilities_API::Files::TextFile
    {
    private:
        RNEMDDataPtr allDataFromFile { std::make_shared<RNEMDData>() };
        RNEMDParametersPtr rnemdParameters { std::make_shared<RNEMDParameters>() };

        std::vector< std::vector<std::string> > superDataVector { getSuperDataVector() };
        std::vector< std::vector<std::string> > superMetaDataVector { getSuperMetaDataVector(" \t\n\";") };

        void setRNEMDData();
        void setRNEMDBlockParameters();
        void setRNEMDReportParameters();
        void setRNEMDInferredParameters();

        int findDataFieldStartLocation(std::string_view dataFieldLabel);

        template <typename T>
        std::vector<T> parseDataFromFile(int startIndex = 0);

    public:
        explicit RNEMDFile(std::string_view FullFileName);

        RNEMDDataPtr getAllDataFromFile() const { return allDataFromFile; }
        RNEMDParametersPtr getRNEMDParameters() const { return rnemdParameters; }
        Utilities_API::Files::FileName getFileName() const { return Utilities_API::Files::TextFile::getFileName(); }
    };
}

#endif
