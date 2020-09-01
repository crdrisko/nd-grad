// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum4.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-07:58:31
// Description: Using accumulation traits to "select" the return type and define a reasonable zero value

#ifndef ACCUM4_HPP
#define ACCUM4_HPP

#include "accumtraits4.hpp"

template<typename T, typename AT = AccumulationTraits<T>>
auto accum(T const* beg, T const* end)
{
    typename AT::AccT total = AT::zero();

    while (beg != end)
    {
        total += *beg;
        ++beg;
    }

    return total;
}

#endif
