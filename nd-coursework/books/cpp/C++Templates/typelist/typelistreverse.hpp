// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: typelistreverse.hpp
// Author: crdrisko
// Date: 09/30/2020-06:49:57
// Description: A metafunction for reversing a typelist

#ifndef TYPELISTREVERSE_HPP
#define TYPELISTREVERSE_HPP

#include "typelistfront.hpp"
#include "typelistisempty.hpp"
#include "typelistpopfront.hpp"
#include "typelistpushback.hpp"

template<typename List, bool Empty = IsEmpty<List>::value>
class ReverseT;

template<typename List>
using Reverse = typename ReverseT<List>::Type;

// recursive case:
template<typename List>
class ReverseT<List, false> : public PushBackT<Reverse<PopFront<List>>, Front<List>>
{
};

// basis case:
template<typename List>
class ReverseT<List, true>
{
public:
    using Type = List;
};

#endif
