// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: fzFile.hpp
// Author: crdrisko
// Date: 03/12/2024-06:39:50
// Description:

#ifndef ND_GRAD_ND_RESEARCH_SRC_FILETYPES_FZFILES_FZFILE_HPP
#define ND_GRAD_ND_RESEARCH_SRC_FILETYPES_FZFILES_FZFILE_HPP

#include <map>
#include <string>
#include <vector>

#include <common-utils/files.hpp>
#include <cpp-units/physicalQuantities.hpp>

namespace ND_Research
{
    struct FZParameters
    {
        CppUnits::Time time {};
        std::size_t numberOfZConstraints {};

        struct FZParameters2
        {
            CppUnits::Force zConstraintForce {};
            CppUnits::Length  currentPosition {};
        };

        std::map<std::size_t, std::vector<FZParameters2>> moleculeData;
    };

    class FZFile
    {
    private:
        std::vector<FZParameters> params_ {};
        std::string fileName_ {};

    public:
        explicit FZFile(const std::string& fileName) : fileName_ {fileName}
        {
            DryChem::FileParser parser {fileName};

            parser.parseDataFile(*this);
        }

        void operator()(const std::string& fileContents_);

        std::vector<FZParameters> getFZParams() const { return params_; }
    };

}   // namespace ND_Research

#endif
