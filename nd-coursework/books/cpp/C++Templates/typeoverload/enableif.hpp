// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: enableif.hpp
// Author: crdrisko
// Date: 09/03/2020-08:06:20
// Description: A simple implementation of the EnableIfT trait, based on std::enable_if<>

#ifndef ENABLEIF_HPP
#define ENABLEIF_HPP

template<bool, typename T = void>
struct EnableIfT
{
};

template<typename T>
struct EnableIfT<true, T>
{
    using Type = T;
};

template<bool Cond, typename T = void>
using EnableIf = typename EnableIfT<Cond, T>::Type;

#endif
