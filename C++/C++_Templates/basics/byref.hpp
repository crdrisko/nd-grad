// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: byref.hpp
// Author: crdrisko
// Date: 08/13/2020-12:12:50
// Description: Missing file from book

#ifndef BYREF_HPP
#define BYREF_HPP

template<typename T>
T const& checked(T const& a, T const& b)
{
    return test() ? a : b;
}

#endif
