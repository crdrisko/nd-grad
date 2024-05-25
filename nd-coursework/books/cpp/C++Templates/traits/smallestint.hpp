// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: smallestint.hpp
// Author: crdrisko
// Date: 08/31/2020-20:18:00
// Description: Determining the smallest integer value type using nested IfThenElse traits

#ifndef SMALLESTINT_HPP
#define SMALLESTINT_HPP

#include <limits>

#include "ifthenelse.hpp"

template<auto N>
struct SmallestIntT
{
    using Type = typename IfThenElseT<N <= std::numeric_limits<char>::max(),
        char,
        typename IfThenElseT<N <= std::numeric_limits<short>::max(),
            short,
            typename IfThenElseT<N <= std::numeric_limits<int>::max(),
                int,
                typename IfThenElseT<N <= std::numeric_limits<long>::max(),
                    long,
                    typename IfThenElseT<N <= std::numeric_limits<long long>::max(),
                        long long,   // then
                        void         // fallback
                        >::Type>::Type>::Type>::Type>::Type;
};

#endif
