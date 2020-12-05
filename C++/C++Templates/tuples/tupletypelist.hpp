// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: tupletypelist.hpp
// Author: crdrisko
// Date: 11/07/2020-07:53:04
// Description: Specializing some basic typelist algorithms for tuples

#ifndef TUPLETYPELIST_HPP
#define TUPLETYPELIST_HPP

#include "../typelist/typelistfront.hpp"
#include "../typelist/typelistisempty.hpp"
#include "../typelist/typelistpopfront.hpp"
#include "../typelist/typelistpushback.hpp"
#include "../typelist/typelistpushfront.hpp"
#include "tuple.hpp"


// determine whether the tuple is empty:
template<>
struct IsEmpty<Tuple<>>
{
    static constexpr bool value = true;
};

// extract front element:
template<typename Head, typename... Tail>
class FrontT<Tuple<Head, Tail...>>
{
public:
    using Type = Head;
};

// remove front element:
template<typename Head, typename... Tail>
class PopFrontT<Tuple<Head, Tail...>>
{
public:
    using Type = Tuple<Tail...>;
};

// add element to the front:
template<typename... Types, typename Element>
class PushFrontT<Tuple<Types...>, Element>
{
public:
    using Type = Tuple<Element, Types...>;
};

// add element to the back:
template<typename... Types, typename Element>
class PushBackT<Tuple<Types...>, Element>
{
public:
    using Type = Tuple<Types..., Element>;
};

#endif
