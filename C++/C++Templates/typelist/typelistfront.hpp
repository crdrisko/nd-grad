// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: typelistfront.hpp
// Author: crdrisko
// Date: 09/10/2020-11:48:09
// Description: A metafunction for extracting the first element from a typelist

#ifndef TYPELISTFRONT_HPP
#define TYPELISTFRONT_HPP

#include "typelist.hpp"

template<typename List>
class FrontT;

template<typename Head, typename... Tail>
class FrontT<Typelist<Head, Tail...>>
{
public:
    using Type = Head;
};

template<typename List>
using Front = typename FrontT<List>::Type;

#endif
