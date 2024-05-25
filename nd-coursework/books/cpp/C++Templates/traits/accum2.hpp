// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum2.hpp
// Author: crdrisko
// Date: 08/18/2020-07:47:02
// Description: Using accumulation traits to "select" the return type of our template function

#ifndef ACCUM2_HPP
#define ACCUM2_HPP

#include "accumtraits2.hpp"

template<typename T>
auto accum(T const* beg, T const* end)
{
    // return type is traits of the element type
    using AccT = typename AccumulationTraits<T>::AccT;

    AccT total {};   // assume this actually creates a zero value

    while (beg != end)
    {
        total += *beg;
        ++beg;
    }

    return total;
}

#endif
