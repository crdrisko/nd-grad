// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: emdFile.hpp
// Author: crdrisko
// Date: 09/18/2023-07:02:20
// Description:

#ifndef ND_GRAD_ND_RESEARCH_INCLUDE_EMDFILE_HPP
#define ND_GRAD_ND_RESEARCH_INCLUDE_EMDFILE_HPP

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <common-utils/files.hpp>
#include <common-utils/strings.hpp>

namespace ND_Research
{
    template<typename ResultType>
    std::vector<ResultType> parseInputFiles(const std::set<std::string>& paths)
    {
        std::vector<ResultType> input;

        for (const auto& path : paths)
        {
            DryChem::FileParser parser {path};
            auto rows = parser.parseDataFile(DryChem::AsRows());

            std::string dataContents {};

            for (const auto& row : rows)
                if (row[0] != '#')
                    dataContents += row + '\n';

            ResultType temp_results {};

            DryChem::AsColumns columnParser {};
            std::vector<std::string> columns {columnParser(dataContents)};

            const int nFields = sizeof(temp_results) / sizeof(temp_results.x);

            if (columns.size() == nFields)
            {
                for (std::size_t i {}; i < columns.size(); ++i)
                {
                    DryChem::Tokenizer tok {columns[i]};
                    std::vector<std::string> splitColumns = tok.split();

                    for (const auto& elem : splitColumns)
                        ((&temp_results.x)[i]).push_back(std::stod(elem));
                }
            }

            input.push_back(temp_results);
        }

        return input;
    }

    template<typename ResultType>
    ResultType calculateAverages(const std::vector<ResultType>& input)
    {
        ResultType output {input[0]};

        for (std::size_t sample {1}; sample < input.size(); ++sample)
        {
            for (std::size_t bin {}; bin < input[sample].x.size(); ++bin)
            {
                const int nFields = sizeof(input[sample]) / sizeof(input[sample].x);

                for (std::size_t i {}; i < nFields; ++i)
                {
                    ((&output.x)[i]).at(bin) += ((&input[sample].x)[i]).at(bin);
                }
            }
        }

        for (std::size_t bin {}; bin < output.x.size(); ++bin)
        {
            const int nFields = sizeof(output) / sizeof(output.x);

            for (std::size_t i {}; i < nFields; ++i)
            {
                ((&output.x)[i]).at(bin) /= input.size();
            }
        }

        return output;
    }

    template<typename ResultType>
    ResultType calculateStdDev(const ResultType& output, const std::vector<ResultType>& input)
    {
        ResultType errors;

        const int nFields = sizeof(output) / sizeof(output.x);

        for (std::size_t i {}; i < nFields; ++i)
        {
            ((&errors.x)[i]).resize(((&output.x)[i]).size());
        }

        for (std::size_t bin {}; bin < output.x.size(); ++bin)
        {
            for (std::size_t sample {}; sample < input.size(); ++sample)
            {
                const int nFields = sizeof(input[sample]) / sizeof(input[sample].x);

                for (std::size_t i {}; i < nFields; ++i)
                {
                    double diff_t = ((&input[sample].x)[i]).at(bin) - ((&output.x)[i]).at(bin);

                    ((&errors.x)[i]).at(bin) += (diff_t * diff_t);
                }
            }

            const int nFields = sizeof(errors) / sizeof(errors.x);

            // Calculates the unbiased sample variance / standard deviation
            for (std::size_t i {}; i < nFields; ++i)
            {
                ((&errors.x)[i]).at(bin) = std::sqrt(((&errors.x)[i]).at(bin) / (input.size() - 1));
            }
        }

        return errors;
    }

    template<typename ResultType>
    void calculate95CIFromStdDev(ResultType& errors, std::size_t nSamples)
    {
        for (std::size_t bin {}; bin < errors.x.size(); ++bin)
        {
            const int nFields = sizeof(errors) / sizeof(errors.x);

            for (std::size_t i {}; i < nFields; ++i)
            {
                ((&errors.x)[i]).at(bin) *= 1.96 / std::sqrt(nSamples);
            }
        }
    }
}   // namespace ND_Research

#endif
