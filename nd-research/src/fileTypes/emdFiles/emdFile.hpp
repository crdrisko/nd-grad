// Copyright (c) 2019-2023 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: emdFile.hpp
// Author: crdrisko
// Date: 09/18/2023-07:02:20
// Description:

#ifndef EMDFILE_HPP
#define EMDFILE_HPP

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
    /* template<typename T>
    class EMDFile
    {
    private:
        T data_ {};
        T errors_ {};
        std::string fileName_ {};

        T parseDataFields(const std::string& dataContents);
        std::string removeQuotes(const std::string& str) const;
        void determineActivity(const std::string& row);
        std::string generateSelectionScript(const std::vector<std::string>& selectionScript) const;

        template<typename T>
        std::string generateVector3Ds(const DryChem::Vector3D<T>& vector2Print) const;

    public:
        explicit EMDFile(const std::string& fileName) : fileName_ {fileName}
        {
            DryChem::FileParser parser {fileName};

            parser.parseDataFile(*this);
        }

        EMDFile(const T& data, const T& errors) : data_ {data}, errors_ {errors} {}

        void operator()(const std::string& fileContents_);

        int determineRegionBounds(const CppUnits::Length& wrappedZCoords) const;

        T getRNEMDData() const { return data_; }
        T getRNEMDErrors() const { return errors_; }

        void writeRNEMDFile(const std::string& fileName) const;
    };

 */

    template<typename ReturnType>
    std::vector<ReturnType> parseInputFiles(const std::set<std::string>& paths)
    {
        std::vector<ReturnType> input;

        for (const auto& path : paths)
        {
            DryChem::FileParser parser {path};
            auto columns = parser.parseDataFile(DryChem::AsColumns());

            ReturnType temp_results {};

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

    template<typename T>
    T calculateAverages(const std::vector<T>& input)
    {
        T output {input[0]};

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

    template<typename T>
    T calculateStdDev(const T& output, const std::vector<T>& input)
    {
        T errors;

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

    template<typename T>
    void calculate95CIFromStdDev(T& errors, std::size_t nSamples)
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
