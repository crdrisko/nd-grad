// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: dataFields.hpp - Version 1.0.0
// Author: crdrisko
// Date: 05/13/2020-11:05:25
// Description: Defines the various types of data fields encountered in OpenMD output files

#ifndef ND_RESEARCH_DATAFIELDS_HPP
#define ND_RESEARCH_DATAFIELDS_HPP

#include <algorithm>
#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include <utils-api/containers.hpp>

namespace ND_Research
{
    class DataField
    {
    private:
        unsigned int labelStartIndex {};
        std::vector<long double> data;

        virtual void appendLabels() {}
        virtual void push(const std::vector<std::string>& currentRow, unsigned int index);

    protected:
        std::string label;
        std::string_view dataLabels;

    public:
        explicit DataField(std::string_view Label) : label{Label} {}
        virtual ~DataField() = default;

        void findLabelStartLocation(std::string_view DataLabels);
        void processData(const std::vector<std::string>& currentRow, unsigned int& dataStartIndex);

        template <typename PhysicalQuantity>
        void convertToPhysicalQuantity(std::vector<PhysicalQuantity>& Data) const
        {
            if ( labelStartIndex != std::numeric_limits<unsigned int>::max() )
            {
                Data.resize(data.size());

                std::transform( data.begin(), data.end(), Data.begin(),
                    [](long double value) { return PhysicalQuantity{value}; } );
            }
        }

        unsigned int getLabelStartIndex() const { return labelStartIndex; }
    };

    using DataFieldPtr = std::shared_ptr<DataField>;


    class DataFieldArray : public DataField
    {
    private:
        Utilities_API::Containers::Vector3D< std::vector<long double> > data;

        virtual void push(const std::vector<std::string>& currentRow, unsigned int index) override;

    public:
        explicit DataFieldArray(std::string_view Label) : DataField{Label} {}

        template <typename PhysicalQuantity>
        void convertToPhysicalQuantity(Utilities_API::Containers::Vector3D< std::vector<PhysicalQuantity> >& Data) const
        {
            for (std::size_t i {}; i < 3; ++i)
            {
                if ( getLabelStartIndex() != std::numeric_limits<unsigned int>::max() )
                {
                    Data[i].resize(data[i].size());

                    std::transform( data[i].begin(), data[i].end(), Data[i].begin(),
                        [](long double value) { return PhysicalQuantity{value}; } );
                }
            }
        }
    };


    class DataFieldVector : public DataField
    {
    private:
        std::vector<std::string> additionalLabels;
        std::vector< std::vector<long double> > data;

        virtual void appendLabels() override;
        virtual void push(const std::vector<std::string>& currentRow, unsigned int index) override;
        void removeEraseExtraneousLabels();

    public:
        DataFieldVector(std::string_view Label, std::vector<std::string> AdditionalLabels)
            : DataField{Label}, additionalLabels{AdditionalLabels} {}

        template <typename PhysicalQuantity>
        void convertToPhysicalQuantity(std::vector< std::vector<PhysicalQuantity> >& Data) const
        {
            if ( getLabelStartIndex() != std::numeric_limits<unsigned int>::max() )
            {
                Data.resize(data.size());

                for (std::size_t i {}; i < additionalLabels.size(); ++i)
                {
                    Data[i].resize(data[i].size());

                    std::transform( data[i].begin(), data[i].end(), Data[i].begin(),
                        [](long double value) { return PhysicalQuantity{value}; } );
                }
            }
        }
    };
}

#endif
