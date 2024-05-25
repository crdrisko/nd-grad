// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: valuelist.hpp
// Author: crdrisko
// Date: 10/02/2020-08:07:39
// Description: A new typelist class for storing the values directly

#ifndef VALUELIST_HPP
#define VALUELIST_HPP

#include "ctvalue.hpp"
#include "typelistfront.hpp"
#include "typelistisempty.hpp"
#include "typelistpopfront.hpp"
#include "typelistpushback.hpp"
#include "typelistpushfront.hpp"

template<typename T, T... Values>
struct Valuelist
{
};

template<typename T, T... Values>
struct IsEmpty<Valuelist<T, Values...>>
{
    static constexpr bool value = sizeof...(Values) == 0;
};

template<typename T, T Head, T... Tail>
struct FrontT<Valuelist<T, Head, Tail...>>
{
    using Type               = CTValue<T, Head>;
    static constexpr T value = Head;
};

template<typename T, T Head, T... Tail>
struct PopFrontT<Valuelist<T, Head, Tail...>>
{
    using Type = Valuelist<T, Tail...>;
};

template<typename T, T... Values, T New>
struct PushFrontT<Valuelist<T, Values...>, CTValue<T, New>>
{
    using Type = Valuelist<T, New, Values...>;
};

template<typename T, T... Values, T New>
struct PushBackT<Valuelist<T, Values...>, CTValue<T, New>>
{
    using Type = Valuelist<T, Values..., New>;
};

#endif
