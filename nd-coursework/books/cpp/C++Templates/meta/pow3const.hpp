// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: pow3const.hpp
// Author: crdrisko
// Date: 09/02/2020-08:24:26
// Description: Computing the powers of 3 using in-class static constant initializers

#ifndef POW3CONST_HPP
#define POW3CONST_HPP

// primary template to compute 3 to the Nth
template<int N>
struct Pow3
{
    static int const value = 3 * Pow3<N - 1>::value;
};

// full specialization to end the recursion
template<>
struct Pow3<0>
{
    static int const value = 1;
};

#endif
