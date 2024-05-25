// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: min2.hpp
// Author: crdrisko
// Date: 09/04/2020-07:55:07
// Description: Computing the minimum of two values, instantiation-safe with the correct set of requirements

#ifndef MIN2_HPP
#define MIN2_HPP

#include "enableif.hpp"
#include "iscontextualbool.hpp"
#include "lessresult.hpp"

template<typename T>
EnableIf<IsContextualBool<LessResult<T const&, T const&>>, T const&> min(T const& x, T const& y)
{
    if (y < x)
        return y;

    return x;
}

#endif
