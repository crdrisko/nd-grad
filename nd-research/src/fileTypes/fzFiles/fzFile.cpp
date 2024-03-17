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

                    params.moleculeData[moleculeIndex].emplace_back(
                        FZParameters::FZParameters2 {Force {splitRow[1]}, Length {splitRow[2]}});
                }

                params_.push_back(params);

                i += (2 + params.numberOfZConstraints);
            }
        }
    }
}   // namespace ND_Research


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <path>\n";
        return EXIT_FAILURE;
    }

    ND_Research::FZFile fzFile {argv[1]};

    auto params = fzFile.getFZParams();

    for (const auto& param : params)
    {
        Force sumForces {};

        std::cout << param.time << ' ' << param.numberOfZConstraints << '\n';

        for (const auto& [id, params2] : param.moleculeData)
        {
            Force sumForces {};

            for (const auto& param2 : params2)
                sumForces += param2.zConstraintForce;

            std::cout << sumForces;
        }
    }
}