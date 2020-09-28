// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: structbind1.hpp
// Author: crdrisko
// Date: 09/28/2020-08:25:56
// Description: Providing a tuple-like API for the Customer class for structured bindings

#ifndef STRUCTBIND1_HPP
#define STRUCTBIND1_HPP

#include <cstddef>
#include <utility>                                          // for tuple-like API

#include "customer1.hpp"

// provide a tuple-like API for class Customer for structured bindings:
template<>
struct std::tuple_size<Customer>
{
    static constexpr int value = 3;                         // we have 3 attributes
};

template<>
struct std::tuple_element<2, Customer>
{
    using type = long;                                      // last element is a long
};

template<std::size_t Idx>
struct std::tuple_element<Idx, Customer>
{
    using type = std::string;                               // the other attributes are strings
};

// define specific getters:
template<std::size_t> auto get(const Customer& c);
template<> auto get<0>(const Customer& c) { return c.getFirst(); }
template<> auto get<1>(const Customer& c) { return c.getLast(); }
template<> auto get<2>(const Customer& c) { return c.getValue(); }

#endif
