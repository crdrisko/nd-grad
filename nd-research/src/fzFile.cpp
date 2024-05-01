// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: fzFile.cpp
// Author: crdrisko
// Date: 03/12/2024-06:39:42
// Description:

#include "fzFile.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <common-utils/files.hpp>
#include <common-utils/math.hpp>
#include <common-utils/strings.hpp>
#include <cpp-units/physicalQuantities.hpp>

using namespace CppUnits;

namespace ND_Research
{
    void FZFile::operator()(const std::string& fileContents_)
    {
        DryChem::AsRows rowParser {};
        std::vector<std::string> rows {rowParser(fileContents_)};

        for (std::size_t i {}; i < rows.size();)
        {
            if (rows[i][0] == '/')
            {
                // skip line comments
                ++i;
                continue;
            }
            else
            {
                FZParameters params {};

                params.time                 = Time {rows[i]};
                params.numberOfZConstraints = std::stoul(rows[i + 1]);

                for (std::size_t j {}; j < params.numberOfZConstraints; ++j)
                {
                    DryChem::Tokenizer tok {rows[i + 2 + j]};
                    std::vector<std::string> splitRow = tok.split();

                    std::size_t moleculeIndex = std::stoul(splitRow[0]);

                    params.moleculeData[moleculeIndex]
                        = FZParameters::ZConstraints {Force {splitRow[1]}, Length {splitRow[2]}, Length {splitRow[3]}};
                }

                params_.push_back(params);

                i += (2 + params.numberOfZConstraints);
            }
        }
    }
}   // namespace ND_Research
