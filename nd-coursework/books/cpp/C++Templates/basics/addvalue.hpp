// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: addvalue.hpp
// Author: crdrisko
// Date: 07/26/2020-17:47:44
// Description: Defines a group of functions for which a certain value can be added

#ifndef ADDVALUE_HPP
#define ADDVALUE_HPP

template<int Val, typename T>
T addValue(T x)
{
    return x + Val;
}

#endif
