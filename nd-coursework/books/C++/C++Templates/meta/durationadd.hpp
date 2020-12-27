// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: durationadd.hpp
// Author: crdrisko
// Date: 09/02/2020-07:50:52
// Description: Adding two durations where unit types might differ

#ifndef DURATIONADD_HPP
#define DURATIONADD_HPP

#include "duration.hpp"
#include "ratio.hpp"
#include "ratioadd.hpp"

template<typename T1, typename U1, typename T2, typename U2>
constexpr auto operator+(Duration<T1, U1> const& lhs, Duration<T2, U2> const& rhs)
{
    // resulting type is a unit with 1 a nominator and
    // the resulting denominator of adding both unit type fractions:
    using VT = Ratio<1, RatioAdd<U1, U2>::den>;

    // resulting value is the sum of both values
    // converted to the resulting unit type:
    auto val = lhs.value() * VT::den / U1::den * U1::num +
               rhs.value() * VT::den / U2::den * U2::num;

    return Duration<decltype(val), VT>(val);
}

#endif
