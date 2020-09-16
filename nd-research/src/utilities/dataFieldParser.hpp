// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: dataFieldParser.hpp - Version 1.0.0
// Author: crdrisko
// Date: 05/13/2020-12:35:13
// Description: A method to parse datafields in text files using the labels of the individual fields

#ifndef ND_RESEARCH_DATAFIELDPARSER_HPP
#define ND_RESEARCH_DATAFIELDPARSER_HPP

#include <algorithm>
#include <string_view>
#include <vector>

#include <utils-api/files.hpp>

#include "dataFields.hpp"

namespace ND_Research
{
    template<typename... TArgs>
    class DataFieldParser
    {
    private:
        std::unique_ptr<Utilities_API::Files::TextFile> inputFile;
        std::vector<DataFieldPtr> dataFields;

        void sortDataFields(std::string_view dataLabels)
        {
            for (auto& dataField : dataFields)
                dataField->findLabelStartIndex(dataLabels);

            std::sort(dataFields.begin(), dataFields.end(), [](DataFieldPtr& dataField1,
                DataFieldPtr& dataField2) { return dataField1->getLabelStartIndex() < dataField2->getLabelStartIndex(); });
        }

    public:
        explicit DataFieldParser(Utilities_API::Files::TextFile InputFile, TArgs&... AllPossibleDataFields)
            : inputFile{ std::make_unique<Utilities_API::Files::TextFile>(InputFile) },
                dataFields{AllPossibleDataFields...} {}

        void parseDataFromFile(std::string_view dataLabels, const std::string& sepatators = " \t\n")
        {
            sortDataFields(dataLabels);

            for (const auto& row : inputFile->getSuperDataVector(sepatators))
            {
                /* Index checking now occurs for each row in the data file, but it's an improvement
                    over iterating through each row for every data field */
                unsigned int dataStartIndex {dataFields[0]->getLabelStartIndex()};

                for (auto& dataField : dataFields)
                    dataField->processData(row, dataStartIndex);
            }
        }
    };
}

#endif
