// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: exprops2.hpp
// Author: crdrisko
// Date: 09/29/2020-08:11:04
// Description: Defining the operators we will ultimately end up using in our desired expression

#ifndef EXPROPS2_HPP
#define EXPROPS2_HPP

#include "exprarray.hpp"
#include "exprops1.hpp"
#include "exprscalar.hpp"

// addition of two Arrays:
template<typename T, typename R1, typename R2>
Array<T, A_Add<T, R1, R2>> operator+(Array<T, R1> const& a, Array<T, R2> const& b)
{
    return Array<T, A_Add<T, R1, R2>>(A_Add<T, R1, R2>(a.rep(), b.rep()));
}

// multiplication of two Arrays:
template<typename T, typename R1, typename R2>
Array<T, A_Mult<T, R1, R2>> operator*(Array<T, R1> const& a, Array<T, R2> const& b)
{
    return Array<T, A_Mult<T, R1, R2>>(A_Mult<T, R1, R2>(a.rep(), b.rep()));
}

// multiplication of scalar and Array:
template<typename T, typename R2>
Array<T, A_Mult<T, A_Scalar<T>, R2>> operator*(T const& s, Array<T, R2> const& b)
{
    return Array<T, A_Mult<T, A_Scalar<T>, R2>>(A_Mult<T, A_Scalar<T>, R2>(A_Scalar<T>(s), b.rep()));
}

// multiplication of Array and scalar, addition of scalar and Array
// addition of Array and scalar
// ...

#endif
