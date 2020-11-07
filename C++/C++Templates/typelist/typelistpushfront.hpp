// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: typelistpushfront.hpp
// Author: crdrisko
// Date: 09/10/2020-11:58:11
// Description: A metafunction for inserting a new element at the front of a typelist

#ifndef TYPELISTPUSHFRONT_HPP
#define TYPELISTPUSHFRONT_HPP

#include "typelist.hpp"

template<typename List, typename NewElement>
class PushFrontT;

template<typename... Elements, typename NewElement>
class PushFrontT<Typelist<Elements...>, NewElement>
{
public:
    using Type = Typelist<NewElement, Elements...>;
};

template<typename List, typename NewElement>
using PushFront = typename PushFrontT<List, NewElement>::Type;

#endif
