// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sarrayops1.hpp
// Author: crdrisko
// Date: 09/27/2020-11:41:12
// Description: Some numeric operators for our simple array template

#ifndef SARRAYOPS1_HPP
#define SARRAYOPS1_HPP

#include <cassert>
#include <cstddef>

#include "sarray1.hpp"

// addition of two SArrays
template<typename T>
SArray<T> operator+(SArray<T> const& a, SArray<T> const& b)
{
    assert(a.size() == b.size());
    SArray<T> result(a.size());

    for (std::size_t k = 0; k < a.size(); ++k)
        result[k] = a[k] + b[k];

    return result;
}

// multiplication of two SArrays
template<typename T>
SArray<T> operator*(SArray<T> const& a, SArray<T> const& b)
{
    assert(a.size() == b.size());
    SArray<T> result(a.size());

    for (std::size_t k = 0; k < a.size(); ++k)
        result[k] = a[k] * b[k];

    return result;
}

// multiplication of scalar and SArray
template<typename T>
SArray<T> operator*(T const& s, SArray<T> const& a)
{
    SArray<T> result(a.size());

    for (std::size_t k = 0; k < a.size(); ++k)
        result[k] = s * a[k];

    return result;
}

// multiplication of SArray and scalar
// addition of scalar and SArray
// addition of SArray and scalar
// ...

#endif
