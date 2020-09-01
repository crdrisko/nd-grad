// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: ifthenelse.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/31/2020-20:09:37
// Description: Selecting between two type parameters based on the value of a Boolean value, based on std::conditional<>

#ifndef IFTHENELSE_HPP
#define IFTHENELSE_HPP

// primary template: yield the second argument by default and rely on
//                   a partial specialization to yield the third argument
//                   if COND is false
template<bool COND, typename TrueType, typename FalseType>
struct IfThenElseT
{
    using Type = TrueType;
};

// partial specialization: false yields third argument
template<typename TrueType, typename FalseType>
struct IfThenElseT<false, TrueType, FalseType>
{
    using Type = FalseType;
};

template<bool COND, typename TrueType, typename FalseType>
using IfThenElse = typename IfThenElseT<COND, TrueType, FalseType>::Type;

#endif
