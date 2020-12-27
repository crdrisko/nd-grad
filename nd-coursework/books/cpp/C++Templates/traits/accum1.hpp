// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum1.hpp
// Author: crdrisko
// Date: 08/17/2020-10:16:37
// Description: First attempt at a function template to accumulate values

#ifndef ACCUM1_HPP
#define ACCUM1_HPP

template<typename T>
T accum(T const* beg, T const* end)
{
    T total {};                                             // assume this actually creates a zero value

    while (beg != end)
    {
        total += *beg;
        ++beg;
    }

    return total;
}

#endif
