// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: elementtype.hpp
// Author: crdrisko
// Date: 08/18/2020-11:48:40
// Description: Partial specializations for a number of different container types

#ifndef ELEMENTTYPE_HPP
#define ELEMENTTYPE_HPP

#include <list>
#include <vector>

template<typename T>
struct ElementT;                                            // primary template

template<typename T>
struct ElementT<std::vector<T>>                             // partial specialization for std::vector
{
    using Type = T;
};

template<typename T>
struct ElementT<std::list<T>>                               // partial specialization for std::list
{
    using Type = T;
};

// ...

template<typename T, std::size_t N>
struct ElementT<T[N]>                                       // partial specialization for arrays of known bounds
{
    using Type = T;
};

template<typename T>
struct ElementT<T[]>                                        // partial specialization for arrays of unknown bounds
{
    using Type = T;
};

// ...

#endif
