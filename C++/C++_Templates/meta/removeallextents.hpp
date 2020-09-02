// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: removeallextents.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/02/2020-07:44:36
// Description: Using recursive template instantiation to perform complex type computations

#ifndef REMOVEALLEXTENTS_HPP
#define REMOVEALLEXTENTS_HPP

#include <cstddef>

// primary template: in general we yield the given type:
template<typename T>
struct RemoveAllExtentsT
{
    using Type = T;
};

// partial specialization for array types (with and without bounds):
template<typename T, std::size_t SZ>
struct RemoveAllExtentsT<T[SZ]>
{
    using Type = typename RemoveAllExtentsT<T>::Type;
};

template<typename T>
using RemoveAllExtents = typename RemoveAllExtentsT<T>::Type;

#endif
