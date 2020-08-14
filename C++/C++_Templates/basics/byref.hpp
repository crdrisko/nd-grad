// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
//
// Name: byref.hpp - Version 1.0.0
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
