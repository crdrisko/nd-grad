// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: maxdecltypedecay.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/25/2020-21:09:44
// Description: Returning the type decayed from T for our max() function

#ifndef MAXDECLTYPEDECAY_HPP
#define MAXDECLTYPEDECAY_HPP

#include <type_traits>

template<typename T1, typename T2>
auto max(T1 a, T2 b) -> typename std::decay<decltype(true?a:b)>::type
{
    return b < a ? a : b;
}

#endif
