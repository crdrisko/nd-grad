// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: testAssertions.hpp - Version 1.0.0
// Author: cdrisko
// Date: 02/07/2020-10:01:48
// Description: Defines an assertion class to be used when testing parameters with GoogleTest

#ifndef ND_RESEARCH_TESTASSERTIONS_HPP
#define ND_RESEARCH_TESTASSERTIONS_HPP

#include <gtest/gtest.h>

template<typename T>
class ParameterAssert
{
private:
    T parameter;

public:
    ParameterAssert() = delete;
    ParameterAssert(const T& Parameter = 0) : parameter{Parameter} {}

    void isTrue() const { ASSERT_TRUE(parameter); }
    void isFalse() const { ASSERT_FALSE(parameter); }
    void hasAValueOf(const T& expectedValue) const { ASSERT_EQ(expectedValue, parameter); }
    void hasAValueNear(const double& expectedValue) const { ASSERT_DOUBLE_EQ(expectedValue, parameter); }
};

template<typename T>
ParameterAssert<T> assertThat(const T& parameter)
{
    ParameterAssert<T> assert {parameter};
    return assert;
}

#endif
