// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: issame.hpp
// Author: crdrisko
// Date: 08/28/2020-21:35:56
// Description: A better implementation of IsSameT using the BoolConstant<> templates, based off std::is_same<>

#ifndef ISSAME_HPP
#define ISSAME_HPP

#include "boolconstant.hpp"

template<typename T1, typename T2>
struct IsSameT : FalseType {};

template<typename T>
struct IsSameT<T, T> : TrueType {};

#endif
