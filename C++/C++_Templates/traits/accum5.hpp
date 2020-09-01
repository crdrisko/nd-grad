// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum5.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-10:04:52
// Description: An accumulator using templated policies for the types of calculations done on the range

#ifndef ACCUM5_HPP
#define ACCUM5_HPP

#include "accumtraits4.hpp"
#include "sumpolicy1.hpp"

template<typename T,
         typename Policy = SumPolicy,
         typename Traits = AccumulationTraits<T>>
auto accum(T const* beg, T const* end)
{
    using AccT = typename Traits::AccT;
    AccT total = Traits::zero();

    while (beg != end)
    {
        Policy::accumulate(total, *beg);
        ++beg;
    }

    return total;
}

#endif
