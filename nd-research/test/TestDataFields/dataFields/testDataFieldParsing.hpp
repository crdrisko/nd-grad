// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testDataFieldParsing.hpp - Version 1.0.0
// Author: cdrisko
// Date: 05/18/2020-07:59:46
// Description: Provides ~100% unit test coverage over the DataFieldParser class and functions

#ifndef ND_RESEARCH_TESTDATAFIELDPARSING_HPP
#define ND_RESEARCH_TESTDATAFIELDPARSING_HPP

#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <utils-api/files.hpp>

#include "../../testAssertions.hpp"
#include "../../../src/utilities/dataFields.hpp"
#include "../../../src/utilities/dataFieldParser.hpp"

namespace ND_Research
{
    GTEST_TEST(testDataFieldParsing, tsvFilesAreParsedCorrectlyWithDifferentTypesOfDataFields)
    {
        Utilities_API::Files::TextFile tsvFile {"testFiles/test.tsv"};
        std::string_view sampleLabel {"#\tsingleField\ttripleField\t\t\tmultiField(type1\ttype2\t)"};
        std::vector<std::string> outputTypes {"type1", "type2"};

        DataFieldPtr singleField { std::make_shared<DataField>("singleField") };
        DataFieldPtr doubleField { std::make_shared<DataField>("doubleField") };
        DataFieldPtr tripleField { std::make_shared<DataFieldArray>("tripleField") };
        DataFieldPtr multiField  { std::make_shared<DataFieldVector>("multiField", outputTypes) };

        DataFieldParser dataFieldParser { tsvFile, singleField,
                                                   doubleField,
                                                   tripleField,
                                                   multiField };

        dataFieldParser.parseDataFromFile(sampleLabel);

        auto singleFieldData { singleField->getData() };
        auto tripleFieldData { dynamic_cast<DataFieldArray*>( tripleField.get() )->getData() };
        auto multiFieldData { dynamic_cast<DataFieldVector*>( multiField.get() )->getData() };

        std::vector<std::vector<std::string>> actualTSVData { tsvFile.getSuperDataVector() };

        for (std::size_t i {}; i < actualTSVData.size(); ++i)
        {
            assertThat(singleFieldData[i]).hasAValueOf(actualTSVData[i][0]);
            assertThat(multiFieldData[0][i]).hasAValueOf(actualTSVData[i][4]);
            assertThat(multiFieldData[1][i]).hasAValueOf(actualTSVData[i][5]);

            for (std::size_t j {}; j < 3; ++j)
                assertThat(tripleFieldData[j][i]).hasAValueOf(actualTSVData[i][1 + j]);
        }
    }

    GTEST_TEST(testDataFieldParsing, csvFilesAreParsedCorrectlyWithDifferentTypesOfDataFields)
    {
        Utilities_API::Files::TextFile csvFile {"testFiles/test.csv"};
        std::string_view sampleLabel {"#,singleField,tripleField,,,multiField(type1,type2,)"};
        std::vector<std::string> outputTypes {"type1", "type2"};
        std::string separators {", \t\n"};

        DataFieldPtr singleField { std::make_shared<DataField>("singleField") };
        DataFieldPtr doubleField { std::make_shared<DataField>("doubleField") };
        DataFieldPtr tripleField { std::make_shared<DataFieldArray>("tripleField") };
        DataFieldPtr multiField  { std::make_shared<DataFieldVector>("multiField", outputTypes) };

        DataFieldParser dataFieldParser { csvFile, singleField,
                                                   doubleField,
                                                   tripleField,
                                                   multiField };

        dataFieldParser.parseDataFromFile(sampleLabel, separators);

        auto singleFieldData { singleField->getData() };
        auto tripleFieldData { dynamic_cast<DataFieldArray*>( tripleField.get() )->getData() };
        auto multiFieldData { dynamic_cast<DataFieldVector*>( multiField.get() )->getData() };

        std::vector<std::vector<std::string>> actualCSVData { csvFile.getSuperDataVector(separators) };

        for (std::size_t i {}; i < actualCSVData.size(); ++i)
        {
            assertThat(singleFieldData[i]).hasAValueOf(actualCSVData[i][0]);
            assertThat(multiFieldData[0][i]).hasAValueOf(actualCSVData[i][4]);
            assertThat(multiFieldData[1][i]).hasAValueOf(actualCSVData[i][5]);

            for (std::size_t j {}; j < 3; ++j)
                assertThat(tripleFieldData[j][i]).hasAValueOf(actualCSVData[i][1 + j]);
        }
    }
}

#endif
