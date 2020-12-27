// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: accum6.hpp
// Author: crdrisko
// Date: 08/18/2020-10:51:55
// Description: Using a templated Policy in the accumulator function template

#ifndef ACCUM6_HPP
#define ACCUM6_HPP

#include "accumtraits4.hpp"
#include "sumpolicy2.hpp"

template<typename T,
         template<typename, typename> class Policy = SumPolicy,
         typename Traits = AccumulationTraits<T>>
auto accum(T const* beg, T const* end)
{
    using AccT = typename Traits::AccT;
    AccT total = Traits::zero();

    while (beg != end)
    {
        Policy<AccT, T>::accumulate(total, *beg);
        ++beg;
    }

    return total;
}

#endif
