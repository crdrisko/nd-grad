// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: cttypelist.hpp
// Author: crdrisko
// Date: 10/02/2020-08:02:38
// Description: An alias template providing a homogeneous list of values, described as a Typelist of CTValues

#ifndef CTTYPELIST_HPP
#define CTTYPELIST_HPP

#include "ctvalue.hpp"

template<typename T, T... Values>
using CTTypelist = Typelist<CTValue<T, Values>...>;

#endif
