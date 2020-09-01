// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: decay.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/18/2020-14:08:22
// Description: A trait producing the same type conversion as passing by value for a template parameter, based off std::decay<>

#ifndef DECAY_HPP
#define DECAY_HPP

#include <cstddef>

#include "removecv.hpp"

template<typename T>
struct DecayT : RemoveCVT<T> {};

template<typename T>
struct DecayT<T[]>
{
    using Type = T*;
};

template<typename T, std::size_t N>
struct DecayT<T[N]>
{
    using Type = T*;
};

template<typename R, typename... Args>
struct DecayT<R(Args...)>
{
    using Type = R(*)(Args...);
};

template<typename R, typename... Args>
struct DecayT<R(Args..., ...)>
{
    using Type = R(*)(Args..., ...);
};

#endif
