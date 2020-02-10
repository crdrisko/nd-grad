// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for license information.
//
// Name: testAssertions.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/07/2020-10:01:48
// Description: Defines an assertion class to be used when testing flux type parameters with GoogleTest

#ifndef TESTASSERTIONS_HPP
#define TESTASSERTIONS_HPP

#include <gtest/gtest.h>
#include "../../rnemd/RNEMDFileParsing/include/rnemdFile.hpp"

namespace OpenMD::RNEMD
{
    template<typename T>
    class FluxTypeAssert
    {
    private:
        T parameter;
        RNEMDFilePtr rnemdFile;

    public:
        FluxTypeAssert() = delete;
        FluxTypeAssert(const RNEMDFilePtr& RNEMDFile, const T& Parameter = 0) : rnemdFile{RNEMDFile},
            parameter{Parameter} {}

        void isTrue() const { ASSERT_TRUE(parameter); }
        void isFalse() const { ASSERT_FALSE(parameter); }
        void hasAValueOf(const T& expectedValue) const { ASSERT_EQ(expectedValue, parameter); }
        void hasAValueNear(const double& expectedValue) const { ASSERT_DOUBLE_EQ(expectedValue, parameter); }
    };

    template<typename T>
    FluxTypeAssert<T> assertThat(const RNEMDFilePtr& rnemdFile, const T& parameter)
    {
        FluxTypeAssert<T> assert {rnemdFile, parameter};
        return assert;
    }
}

#endif
