// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum3.hpp
// Author: crdrisko
// Date: 08/18/2020-07:54:27
// Description: Using accumulation traits to "select" the return type and define a reasonable zero value

#ifndef ACCUM3_HPP
#define ACCUM3_HPP

#include "accumtraits3.hpp"

template<typename T>
auto accum(T const* beg, T const* end)
{
    // return type is traits of the element type
    using AccT = typename AccumulationTraits<T>::AccT;

    AccT total = AccumulationTraits<T>::zero;               // init total by trait value

    while (beg != end)
    {
        total += *beg;
        ++beg;
    }

    return total;
}

#endif
