// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: maxconstexpr.hpp
// Author: crdrisko
// Date: 07/26/2020-08:34:31
// Description: A version of the max() function that can be used at compile time

#ifndef MAXCONSTEXPR_HPP
#define MAXCONSTEXPR_HPP

template<typename T1, typename T2>
constexpr auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif
