// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: maketuple.hpp
// Author: crdrisko
// Date: 10/19/2020-10:17:31
// Description: Using deduction to determine the element types of the Tuple it returns

#ifndef MAKETUPLE_HPP
#define MAKETUPLE_HPP

#include <type_traits>
#include <utility>

#include "tuple.hpp"

template<typename... Types>
auto makeTuple(Types&&... elems)
{
    return Tuple<std::decay_t<Types>...>(std::forward<Types>(elems)...);
}

#endif
