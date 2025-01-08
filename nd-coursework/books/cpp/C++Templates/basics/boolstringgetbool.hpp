// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: boolstringgetbool.hpp
// Author: crdrisko
// Date: 07/30/2020-21:51:13
// Description: Full specialization for BoolString::getValue<>() for bool

#ifndef BOOLSTRINGGETBOOL_HPP
#define BOOLSTRINGGETBOOL_HPP

#include "boolstring.hpp"

template<>
inline bool BoolString::get<bool>() const
{
    return value == "true" || value == "1" || value == "on";
}

#endif
