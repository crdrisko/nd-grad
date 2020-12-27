// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: typelistpopfront.hpp
// Author: crdrisko
// Date: 09/10/2020-11:53:38
// Description: A metafunction for removing the first element from a typelist

#ifndef TYPELISTPOPFRONT_HPP
#define TYPELISTPOPFRONT_HPP

#include "typelist.hpp"

template<typename List>
class PopFrontT;

template<typename Head, typename... Tail>
class PopFrontT<Typelist<Head, Tail...>>
{
public:
    using Type = Typelist<Tail...>;
};

template<typename List>
using PopFront = typename PopFrontT<List>::Type;

#endif
