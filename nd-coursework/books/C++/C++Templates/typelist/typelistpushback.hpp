// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: typelistpushback.hpp
// Author: crdrisko
// Date: 09/13/2020-10:01:41
// Description: A metafunction for inserting a new element at the back of a typelist

#ifndef TYPELISTPUSHBACK_HPP
#define TYPELISTPUSHBACK_HPP

#include "typelist.hpp"

template<typename List, typename NewElement>
class PushBackT;

template<typename...Elements, typename NewElement>
class PushBackT<Typelist<Elements...>, NewElement>
{
public:
    using Type = Typelist<Elements..., NewElement>;
};

template<typename List, typename NewElement>
using PushBack = typename PushBackT<List, NewElement>::Type;

#endif
