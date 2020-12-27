// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: using2.hpp
// Author: crdrisko
// Date: 10/31/2020-15:51:18
// Description: Using multiple using statements to inherit all constructors from a base class

#ifndef USING2_HPP
#define USING2_HPP

template<typename T>
class Base
{
    T value {};

public:
    Base()
    {
        // ...
    }
    Base(T v) : value {v}
    {
        // ...
    }

    // ...
};

template<typename... Types>
class Multi : private Base<Types>...
{
public:
    // derive all constructors:
    using Base<Types>::Base...;

    // ...
};

#endif
