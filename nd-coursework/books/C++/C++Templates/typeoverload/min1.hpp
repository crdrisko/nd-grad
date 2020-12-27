// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: min1.hpp
// Author: crdrisko
// Date: 09/04/2020-07:55:07
// Description: Computing the minimum of two values

#ifndef MIN1_HPP
#define MIN1_HPP

#include "enableif.hpp"
#include "isconvertible.hpp"
#include "lessresult.hpp"

template<typename T>
EnableIf<IsConvertible<LessResult<T const&, T const&>, bool>, T const&>
min(T const& x, T const& y)
{
    if (y < x)
        return y;

    return x;
}

#endif
