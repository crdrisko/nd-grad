// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isarray.hpp
// Author: crdrisko
// Date: 09/01/2020-09:25:14
// Description: Determining if a type is an array, based on std::is_array<>

#ifndef ISARRAY_HPP
#define ISARRAY_HPP

#include <cstddef>

// primary template: not an array
template<typename T>
struct IsArrayT : std::false_type
{
};

// partial specialization for arrays:
template<typename T, std::size_t N>
struct IsArrayT<T[N]> : std::true_type
{
    using BaseT                       = T;
    static constexpr std::size_t size = N;
};

// partial specialization for unbounded arrays:
template<typename T>
struct IsArrayT<T[]> : std::true_type
{
    using BaseT                       = T;
    static constexpr std::size_t size = 0;
};

#endif
