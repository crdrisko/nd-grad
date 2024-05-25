// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: pow3enum.hpp
// Author: crdrisko
// Date: 09/02/2020-08:24:19
// Description: Computing the powers of 3 using an enumeration

#ifndef POW3ENUM_HPP
#define POW3ENUM_HPP

// primary template to compute 3 to the Nth
template<int N>
struct Pow3
{
    enum
    {
        value = 3 * Pow3<N - 1>::value
    };
};

// full specialization to end the recursion
template<>
struct Pow3<0>
{
    enum
    {
        value = 1
    };
};

#endif
