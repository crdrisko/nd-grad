// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: len1.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/12/2020-14:13:41
// Description: Demonstrating SFINAE when determining the length of an array-like type

#ifndef LEN1_HPP
#define LEN1_HPP

#include <cstddef>

// number of elements in a raw array:
template<typename T, unsigned N>
std::size_t len(T(&)[N])
{
    return N;
}

// number of elements for a type having size_type:
template<typename T>
typename T::size_type len(T const& t)
{
    return t.size();
}

#endif
