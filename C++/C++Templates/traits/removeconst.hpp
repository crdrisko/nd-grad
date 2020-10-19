// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for move information.
//
// Name: removeconst.hpp
// Author: crdrisko
// Date: 08/18/2020-13:16:09
// Description: A trait for removing const qualifiers from a template parameter, based off std::remove_const<>

#ifndef REMOVECONST_HPP
#define REMOVECONST_HPP

template<typename T>
struct RemoveConstT
{
    using Type = T;
};

template<typename T>
struct RemoveConstT<T const>
{
    using Type = T;
};

template<typename T>
using RemoveConst = typename RemoveConstT<T>::Type;

#endif
