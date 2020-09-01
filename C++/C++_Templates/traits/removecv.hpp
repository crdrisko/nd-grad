// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for move information.
//
// Name: removecv.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-13:16:29
// Description: A trait for removing const and volatile qualifiers from a template parameter, based off std::remove_cv<>

#ifndef REMOVECV_HPP
#define REMOVECV_HPP

#include "removeconst.hpp"
#include "removevolatile.hpp"

template<typename T>
struct RemoveCVT : RemoveConstT<typename RemoveVolatileT<T>::Type> {};

template<typename T>
using RemoveCV = typename RemoveCVT<T>::Type;

#endif
