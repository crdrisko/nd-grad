// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: len2.hpp
// Author: crdrisko
// Date: 08/12/2020-14:21:08
// Description: Demonstrating SFINAE when determining the length of an array-like type with an elipses for other types

#ifndef LEN2_HPP
#define LEN2_HPP

#include <cstddef>

// number of elements in a raw array:
template<typename T, unsigned N>
std::size_t len(T (&)[N])
{
    return N;
}

// number of elements for a type having size_type:
template<typename T>
typename T::size_type len(T const& t)
{
    return t.size();
}

// fallback for all other types:
std::size_t len(...) { return 0; }

#endif
