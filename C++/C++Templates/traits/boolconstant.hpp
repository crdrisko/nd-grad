// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: boolconstant.hpp
// Author: crdrisko
// Date: 08/28/2020-21:34:03
// Description: Boolean constants to be used as the possible outcomes of IsSameT, based off std::bool_constant

#ifndef BOOLCONSTANT_HPP
#define BOOLCONSTANT_HPP

template<bool val>
struct BoolConstant
{
    using Type = BoolConstant<val>;
    static constexpr bool value = val;
};

using TrueType  = BoolConstant<true>;
using FalseType = BoolConstant<false>;

#endif
