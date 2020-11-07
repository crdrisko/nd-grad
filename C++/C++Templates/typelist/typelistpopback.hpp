// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: typelistpopback.hpp
// Author: crdrisko
// Date: 09/30/2020-07:16:29
// Description: A metafunction for removing the last element from a typelist

#ifndef TYPELISTPOPBACK_HPP
#define TYPELISTPOPBACK_HPP

#include "typelistpopfront.hpp"
#include "typelistreverse.hpp"

template<typename List>
class PopBackT
{
public:
    using Type = Reverse<PopFront<Reverse<List>>>;
};

template<typename List>
using PopBack = typename PopBackT<List>::Type;

#endif
