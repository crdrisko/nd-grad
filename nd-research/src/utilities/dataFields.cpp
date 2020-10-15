// Copyright (c) 2019-2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: dataFields.cpp - Version 1.0.0
// Author: cdrisko
// Date: 05/13/2020-11:05:28
// Description: Provides the class and function definitions for the DataField family of classes

#include <algorithm>
#include <cstddef>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

#include <utils-api/strings.hpp>

#include "dataFields.hpp"

namespace ND_Research
{
    /* A standard data field wraps a single column of data from a data file and is best used for
        scalar quantities */
    void DataField::push(const std::vector<std::string>& currentRow, unsigned int index)
    {
        data.push_back(currentRow[index]);
    }

    void DataField::findLabelStartIndex(std::string_view DataLabels)
    {
        dataLabels = DataLabels;

        labelStartIndex = (Utilities_API::Strings::stringFinder(label, dataLabels)) ?
            dataLabels.find(label) : std::numeric_limits<unsigned int>::max();
    }

    void DataField::processData(const std::vector<std::string>& currentRow, unsigned int& dataStartIndex)
    {
        if ( labelStartIndex != std::numeric_limits<unsigned int>::max() )
        {
            appendLabels();

            unsigned int index {labelStartIndex - dataStartIndex};
            dataStartIndex += label.length();

            push(currentRow, index);
        }
    }


    /* The data field array type wraps three data columns, used for data types with x, y, and z
        components */
    void DataFieldArray::push(const std::vector<std::string>& currentRow, unsigned int index)
    {
        for (std::size_t i {}; i < 3; ++i)
            data[i].push_back(currentRow[index + i]);
    }


    /* Data field vector type determines the number of columns through the additional output types
        passed to the constructor */
    void DataFieldVector::push(const std::vector<std::string>& currentRow, unsigned int index)
    {
        for (std::size_t i {}; i < additionalLabels.size(); ++i)
            data[i].push_back(currentRow[index + i]);
    }

    void DataFieldVector::removeEraseExtraneousLabels()
    {
        auto firstLabelToErase { std::remove_if( additionalLabels.begin(), additionalLabels.end(),
            [&](std::string additionalLabel) { return !Utilities_API::Strings::stringFinder(additionalLabel,
                this->dataLabels); } ) };

        additionalLabels.erase(firstLabelToErase, additionalLabels.end());
    }

    void DataFieldVector::appendLabels()
    {
        if (static int count {}; count++ == 0)
        {
            removeEraseExtraneousLabels();

            if (additionalLabels.size() != 0)
            {
                this->label += '(';

                for (const auto& additionalLabel : additionalLabels)
                    this->label += additionalLabel + '\t';

                this->label += ')';
            }

            data.resize(additionalLabels.size());
        }
    }
}
