// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: conspushfront.hpp
// Author: crdrisko
// Date: 10/02/2020-08:35:46
// Description: A metafunction for inserting a new element at the front of a cons-style typelist

#ifndef CONSPUSHFRONT_HPP
#define CONSPUSHFRONT_HPP

#include "cons.hpp"

template<typename List, typename Element>
class PushFrontT
{
public:
    using Type = Cons<Element, List>;
};

template<typename List, typename Element>
using PushFront = typename PushFrontT<List, Element>::Type;

#endif
