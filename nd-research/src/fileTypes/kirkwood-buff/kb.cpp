// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: kb.cpp
// Author: crdrisko
// Date: 06/23/2023-09:24:34
// Description:

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <common-utils/files.hpp>
#include <common-utils/strings.hpp>

namespace fs = std::filesystem;

struct Results
{
    std::vector<double> r;

    std::vector<double> G11;
    std::vector<double> G12;
    std::vector<double> G22;
};

int main(int argc, char* argv[])
{
    std::string dirName {argv[1]};
    fs::path outputFileName {dirName};
    std::string fileName = outputFileName.string() + "/../" + outputFileName.stem().string();

    std::vector<Results> input;

    std::set<std::string> paths;
    for (const auto& dirEntry : fs::directory_iterator(argv[1]))
        if (dirEntry.path().extension().string() == ".kirkwood-buff")
            paths.insert(dirEntry.path().string());

    int count = 0;

    for (const auto& path : paths)
    {
        DryChem::FileParser parser {path};
        auto columns = parser.parseDataFile(DryChem::AsColumns());

        Results temp_results {};

        for (std::size_t i {}; i < columns.size(); ++i)
        {
            DryChem::Tokenizer tok {columns[i]};
            std::vector<std::string> splitColumns = tok.split();

            for (const auto& elem : splitColumns)
            {
                if (i == 0)
                    temp_results.r.push_back(std::stod(elem));
                if (i == 7)
                    temp_results.G11.push_back(std::stod(elem));
                 if (i == 8)
                    temp_results.G12.push_back(std::stod(elem));
                 if (i == 9)
                    temp_results.G22.push_back(std::stod(elem));
            }
        }

        input.push_back(temp_results);
    }

    Results output {input[0]};

    for (std::size_t sample {1}; sample < input.size(); ++sample)
    {
        for (std::size_t bin {}; bin < input[sample].r.size(); ++bin)
        {
            output.r[bin] += input[sample].r[bin];

            output.G11[bin] += input[sample].G11[bin];
            output.G12[bin] += input[sample].G12[bin];
            output.G22[bin] += input[sample].G22[bin];
        }
    }

    for (std::size_t bin {}; bin < output.r.size(); ++bin)
    {
        output.r[bin] /= input.size();

        output.G11[bin] /= input.size();
        output.G12[bin] /= input.size();
        output.G22[bin] /= input.size();
    }

    Results errors = output;

    for (std::size_t bin {}; bin < output.r.size(); ++bin)
    {
        double sum_r {};

        double sum_G11 {};
        double sum_G12 {};
        double sum_G22 {};

        for (std::size_t sample {}; sample < input.size(); ++sample)
        {
            double diff_r = input[sample].r[bin] - output.r[bin];

            double diff_G11 = input[sample].G11[bin] - output.G11[bin];
            double diff_G12 = input[sample].G12[bin] - output.G12[bin];
            double diff_G22 = input[sample].G22[bin] - output.G22[bin];

            sum_r += (diff_r * diff_r);

            sum_G11 += (diff_G11 * diff_G11);
            sum_G12 += (diff_G12 * diff_G12);
            sum_G22 += (diff_G22 * diff_G22);
        }

        errors.r[bin] = 1.96 * std::sqrt(sum_r / input.size()) / std::sqrt(input.size() - 1);

        errors.G11[bin] = 1.96 * std::sqrt(sum_G11 / input.size()) / std::sqrt(input.size() - 1);
        errors.G12[bin] = 1.96 * std::sqrt(sum_G12 / input.size()) / std::sqrt(input.size() - 1);
        errors.G22[bin] = 1.96 * std::sqrt(sum_G22 / input.size()) / std::sqrt(input.size() - 1);

        if (std::abs(errors.r[bin]) < 1e-16)
            errors.r[bin] = 0.0;
    }

    std::ofstream outputFileStream;
    outputFileStream.open(fileName + ".txt");

    outputFileStream.precision(8);

    for (std::size_t bin {}; bin < output.r.size(); ++bin)
    {
        outputFileStream << output.r[bin] << '\t' << output.G11[bin] << '\t' << output.G12[bin] << '\t' << output.G22[bin]
                         << '\t' << errors.G11[bin] << '\t' << errors.G12[bin] << '\t' << errors.G22[bin]
                         << '\n';
    }
}
