// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: exprops4.hpp
// Author: crdrisko
// Date: 09/29/2020-08:11:10
// Description: Definition of the non-const version of the subscript operator if assignments were enabled in the Array<> class

#ifndef EXPROPS4_HPP
#define EXPROPS4_HPP

#include "exprarray.hpp"
#include "exprops3.hpp"

template<typename T, typename R>
    template<typename T2, typename R2>
Array<T, A_Subscript<T, R, R2>> Array<T, R>::operator[](Array<T2, R2> const& b)
{
    return Array<T, A_Subscript<T, R, R2>>(A_Subscript<T, R, R2>(*this, b));
}

#endif
