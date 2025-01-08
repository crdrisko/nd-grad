// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: max1.hpp
// Author: crdrisko
// Date: 07/25/2020-20:34:40
// Description: A function template that returns the maximum of two values

#ifndef MAX1_HPP
#define MAX1_HPP

template<typename T>
T max(T a, T b)
{
    // if b < a then yield a else yield b
    return b < a ? a : b;
}

#endif
