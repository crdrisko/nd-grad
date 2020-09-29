// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: exprops1a.hpp
// Author: crdrisko
// Date: 09/29/2020-07:22:02
// Description: Helper traits class to select how to refer to an expression template node
//  - in general by reference
//  - for scalars by value

#ifndef EXPROPS1A_HPP
#define EXPROPS1A_HPP

template<typename T> class A_Scalar;

// primary template
template<typename T>
class A_Traits
{
public:
    using ExprRef = T const&;                               // type to refer to is constant reference
};

// partial specialization for scalars
template<typename T>
class A_Traits<A_Scalar<T>>
{
public:
    using ExprRef = A_Scalar<T>;                        // type to refer to is ordinary value
};

#endif
