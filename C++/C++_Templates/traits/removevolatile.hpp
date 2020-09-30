// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for move information.
//
// Name: removevolatile.hpp
// Author: crdrisko
// Date: 08/18/2020-13:16:17
// Description: A trait for removing volatile qualifiers from a template parameter, based off std::remove_volatile<>

#ifndef REMOVEVOLATILE_HPP
#define REMOVEVOLATILE_HPP

template<typename T>
struct RemoveVolatileT
{
    using Type = T;
};

template<typename T>
struct RemoveVolatileT<volatile T>
{
    using Type = T;
};

template<typename T>
using RemoveVolatile = typename RemoveVolatileT<T>::Type;

#endif
