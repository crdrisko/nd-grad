// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: typelistisempty.hpp
// Author: crdrisko
// Date: 09/12/2020-17:46:14
// Description: A metafunction for determining whether a typelist is empty

#ifndef TYPELISTISEMPTY_HPP
#define TYPELISTISEMPTY_HPP

#include "typelist.hpp"

template<typename List>
class IsEmpty
{
public:
    static constexpr bool value = false;
};

template<>
class IsEmpty<Typelist<>>
{
public:
    static constexpr bool value = true;
};

#endif
