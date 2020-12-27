// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: consisempty.hpp
// Author: crdrisko
// Date: 10/02/2020-08:35:46
// Description: A metafunction for to determine whether a cons-style typelist is empty

#ifndef CONSISEMPTY_HPP
#define CONSISEMPTY_HPP

#include "cons.hpp"

template<typename List>
struct IsEmpty
{
    static constexpr bool value = false;
};

template<>
struct IsEmpty<Nil>
{
    static constexpr bool value = true;
};

#endif
