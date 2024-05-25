// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sqrt1.hpp
// Author: crdrisko
// Date: 09/02/2020-08:11:08
// Description: Computing a square root of an integer using recursive instantiation

#ifndef SQRT1_HPP
#define SQRT1_HPP

// primary template to compute sqrt(N)
template<int N, int LO = 1, int HI = N>
struct Sqrt
{
    // compute the midpoint, rounded up
    static constexpr auto mid = (LO + HI + 1) / 2;

    // search a not too large value in a halved interval
    static constexpr auto value = (N < mid * mid) ? Sqrt<N, LO, mid - 1>::value : Sqrt<N, mid, HI>::value;
};

// partial specialization for the case when LO equals HI
template<int N, int M>
struct Sqrt<N, M, M>
{
    static constexpr auto value = M;
};

#endif
