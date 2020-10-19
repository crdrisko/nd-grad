// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: sarrayops2.hpp
// Author: crdrisko
// Date: 09/27/2020-11:51:48
// Description: Providing the definitions of the operation-assignment operators for SArrays

#ifndef SARRAYOPS2_HPP
#define SARRAYOPS2_HPP

#include <cassert>
#include <cstddef>

#include "sarray2.hpp"

// additive assignment of SArray
template<typename T>
SArray<T>& SArray<T>::operator+=(SArray<T> const& b)
{
    assert(size() == b.size());

    for (std::size_t k = 0; k < size(); ++k)
        (*this)[k] += b[k];

    return *this;
}

// multiplicative assignment of SArray
template<typename T>
SArray<T>& SArray<T>::operator*=(SArray<T> const& b)
{
    assert(size() == b.size());

    for (std::size_t k = 0; k < size(); ++k)
        (*this)[k] *= b[k];

    return *this;
}

// multiplicative assignment of scalar
template<typename T>
SArray<T>& SArray<T>::operator*=(T const& s)
{
    for (std::size_t k = 0; k < size(); ++k)
        (*this)[k] *= s;

    return *this;
}

#endif
