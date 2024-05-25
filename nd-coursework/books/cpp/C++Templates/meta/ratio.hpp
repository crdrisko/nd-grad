// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ratio.hpp
// Author: crdrisko
// Date: 09/02/2020-07:50:27
// Description: Keeping track of units in terms of a ratio (fraction) of a principal unit

#ifndef RATIO_HPP
#define RATIO_HPP

template<unsigned N, unsigned D = 1>
struct Ratio
{
    static constexpr unsigned num = N;   // numerator
    static constexpr unsigned den = D;   // denominator

    using Type = Ratio<num, den>;
};

#endif
