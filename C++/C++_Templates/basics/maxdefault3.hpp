// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: maxdefault3.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/26/2020-08:10:38
// Description: Overloading the max() function template to explicitly specify the return type only

#ifndef MAXDEFAULT3_HPP
#define MAXDEFAULT3_HPP

template<typename T1, typename T2>
auto max(T1 a, T2 b)
{
    return b < a ? a : b;
}

template<typename RT, typename T1, typename T2>
RT max(T1 a, T2 b)
{
    return b < a ? a : b;
}

#endif
