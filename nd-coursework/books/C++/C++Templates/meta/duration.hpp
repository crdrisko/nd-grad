// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: duration.hpp
// Author: crdrisko
// Date: 09/02/2020-07:50:42
// Description: Duration type for values of type T with unit type U

#ifndef DURATION_HPP
#define DURATION_HPP

#include "ratio.hpp"

template<typename T, typename U = Ratio<1>>
class Duration
{
public:
    using ValueType = T;
    using UnitType  = typename U::Type;

private:
    ValueType val;

public:
    constexpr Duration(ValueType v = 0) : val(v) {}
    constexpr ValueType value() const { return val; }
};

#endif
