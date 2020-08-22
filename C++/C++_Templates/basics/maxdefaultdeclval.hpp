// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: maxdefaultdeclval.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/13/2020-13:26:36
// Description: Deducing the return type from the passed template parameters

#ifndef MAXDEFAULTDECLVAL_HPP
#define MAXDEFAULTDECLVAL_HPP

#include <utility>

template<typename T1, typename T2,
         typename RT = std::decay_t<decltype(true ? std::declval<T1>()
                                                  : std::declval<T2>())>>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif
