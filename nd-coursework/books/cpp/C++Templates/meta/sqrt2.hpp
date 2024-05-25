// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sqrt2.hpp
// Author: crdrisko
// Date: 09/02/2020-08:11:24
// Description: Reducing the explosion in the number of template instantiations using our IfThenElse trait

#ifndef SQRT2_HPP
#define SQRT2_HPP

#include "../traits/ifthenelse.hpp"

// primary template for main recursive step
template<int N, int LO = 1, int HI = N>
struct Sqrt
{
    // compute the midpoint, rounded up
    static constexpr auto mid = (LO + HI + 1) / 2;

    // search a not too large value in a halved interval
    using SubT = IfThenElse<(N < mid * mid), Sqrt<N, LO, mid - 1>, Sqrt<N, mid, HI>>;

    static constexpr auto value = SubT::value;
};

// partial specialization for the case when LO equals HI
template<int N, int S>
struct Sqrt<N, S, S>
{
    static constexpr auto value = S;
};

#endif
