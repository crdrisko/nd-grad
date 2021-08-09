// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: isnothrowmovable.hpp
// Author: crdrisko
// Date: 08/09/2021-15:18:14
// Description: Type trait to check whether a base class guarantees not to throw in the move constructor (even if the constructor is not callable)

#ifndef ISNOTHROWMOVABLE_HPP
#define ISNOTHROWMOVABLE_HPP

#include <type_traits>

template<typename Base>
struct Wrapper : Base
{
    using Base::Base;

    // implement all possibly wrapped pure virtual functions:
    void print() const {}

    // ...
};

template<typename T>
static constexpr inline bool is_nothrow_movable_v = std::is_nothrow_move_constructible_v<Wrapper<T>>;

#endif
