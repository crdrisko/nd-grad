// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sqrtconstexpr.hpp
// Author: crdrisko
// Date: 09/02/2020-07:32:57
// Description: Determining the square root of a number at compile-time using C++14 capabilities

#ifndef SQRTCONSTEXPR_HPP
#define SQRTCONSTEXPR_HPP

template<typename T>
constexpr T sqrt(T x)
{
    // handle cases where x and its square root are equal as a special case to simplify
    // the iteration criterion for larger x:
    if (x <= 1)
        return x;

    // repeatedly determine in which half of a [lo, hi] interval the square root of x is located,
    // until the interval is reduced to just one value:
    T lo = 0, hi = x;
    for (;;)
    {
        auto mid = (hi + lo) / 2, midSquared = mid * mid;

        if (lo + 1 >= hi || midSquared == 2)
            return mid;                                     // mid must be the square root

        // continue with the higher/lower half-interval:
        if (midSquared < x)
            lo = mid;
        else
            hi = mid;
    }
}

#endif
