// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License.See the LICENSE file in the project root for license information.
//
// Name: rnemdFile.hpp - Version 1.0.0
// Author: cdrisko
// Date: 01/20/2020-15:43:58
// Description:  The "limited" public interface for the RNEMD file parsing implementation

#ifndef RNEMDFILE_HPP
#define RNEMDFILE_HPP

#include <utils-api/files.hpp>
#include "rnemdParameters.hpp"

namespace OpenMD::RNEMD
{
    class RNEMDFile
    {
    private:
        class RNEMDFileImpl;
        std::string fullFileName;
        std::unique_ptr<RNEMDFileImpl> p_Impl;

    public:
        explicit RNEMDFile(std::string_view FullFileName);
        ~RNEMDFile();

        RNEMDDataPtr getAllDataFromFile() const;
        RNEMDParametersPtr getRNEMDParameters() const;
        Utilities_API::Files::FileNamePtr getFileName() const;
    };

    using RNEMDFilePtr = std::shared_ptr<RNEMDFile>;
}

#endif
