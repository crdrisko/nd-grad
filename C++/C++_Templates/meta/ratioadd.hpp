// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ratioadd.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/02/2020-07:50:32
// Description: Adding two ratios at compile time

#ifndef RATIOADD_HPP
#define RATIOADD_HPP

#include "ratio.hpp"

// implementation of adding two ratios:
template<typename R1, typename R2>
struct RatioAddImpl
{
private:
    static constexpr unsigned den = R1::den * R2::den;
    static constexpr unsigned num = R1::num * R2::den + R2::num * R1::den;

public:
    typedef Ratio<num, den> Type;
};

// using declaration for convient usage:
template<typename R1, typename R2>
using RatioAdd = typename RatioAddImpl<R1, R2>::Type;

#endif
