// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: largesttype.hpp
// Author: crdrisko
// Date: 09/12/2020-17:33:06
// Description: A metafunction for finding the largest type within a typelist

#ifndef LARGESTTYPE_HPP
#define LARGESTTYPE_HPP

#include "../traits/ifthenelse.hpp"
#include "typelist.hpp"
#include "typelistfront.hpp"
#include "typelistpopfront.hpp"

template<typename List>
class LargestTypeT;

// recursive case:
template<typename List>
class LargestTypeT
{
private:
    using First = Front<List>;
    using Rest  = typename LargestTypeT<PopFront<List>>::Type;

public:
    using Type = IfThenElse<(sizeof(First) >= sizeof(Rest)), First, Rest>;
};

// basis case:
template<>
class LargestTypeT<Typelist<>>
{
public:
    using Type = char;
};

template<typename List>
using LargestType = typename LargestTypeT<List>::Type;

#endif
