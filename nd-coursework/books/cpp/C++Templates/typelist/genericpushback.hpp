// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: genericpushback.hpp
// Author: crdrisko
// Date: 09/30/2020-06:34:33
// Description: A more generic metafunction for inserting a new element at the back of a typelist

#ifndef GENERICPUSHBACK_HPP
#define GENERICPUSHBACK_HPP

#include "typelistfront.hpp"
#include "typelistisempty.hpp"
#include "typelistpopfront.hpp"
#include "typelistpushfront.hpp"

template<typename List, typename NewElement, bool = IsEmpty<List>::value>
class PushBackRecT;

// recursive case:
template<typename List, typename NewElement>
class PushBackRecT<List, NewElement, false>
{
    using Head    = Front<List>;
    using Tail    = PopFront<List>;
    using NewTail = typename PushBackRecT<Tail, NewElement>::Type;

public:
    using Type = PushFront<Head, NewTail>;
};

// basis case:
template<typename List, typename NewElement>
class PushBackRecT<List, NewElement, true>
{
public:
    using Type = PushFront<List, NewElement>;
};

// generic push-back operation:
template<typename List, typename NewElement>
class PushBackT : public PushBackRecT<List, NewElement>
{
};

template<typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;

#endif
