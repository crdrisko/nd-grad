// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: genericlargesttype.hpp
// Author: crdrisko
// Date: 09/12/2020-17:48:20
// Description: A more generic metafunction for finding the largest type within a typelist

#ifndef GENERICLARGESTTYPE_HPP
#define GENERICLARGESTTYPE_HPP

#include "typelistisempty.hpp"
#include "typelistfront.hpp"
#include "typelistpopfront.hpp"
#include "../traits/ifthenelse.hpp"

template<typename List, bool Empty = IsEmpty<List>::value>
class LargestTypeT;

// recursive case:
template<typename List>
class LargestTypeT<List, false>
{
private:
    using Contender = Front<List>;
    using Best = typename LargestTypeT<PopFront<List>>::Type;

public:
    using Type = IfThenElse<(sizeof(Contender) >= sizeof(Best)), Contender, Best>;
};

// basis case:
template<typename List>
class LargestTypeT<List, true>
{
public:
    using Type = char;
};

template<typename List>
using LargestType = typename LargestTypeT<List>::Type;

#endif
