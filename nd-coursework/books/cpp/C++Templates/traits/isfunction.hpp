// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isfunction.hpp
// Author: crdrisko
// Date: 09/01/2020-09:37:11
// Description: Determining if a type is a function, based on std::is_function<>

#ifndef ISFUNCTION_HPP
#define ISFUNCTION_HPP

#include <type_traits>

#include "../typelist/typelist.hpp"

// primary template: no function
template<typename T>
struct IsFunctionT : std::false_type
{
};

// functions:
template<typename R, typename... Params>
struct IsFunctionT<R(Params...)> : std::true_type
{
    using Type                     = R;
    using ParamsT                  = Typelist<Params...>;
    static constexpr bool variadic = false;
};

// variadic functions:
template<typename R, typename... Params>
struct IsFunctionT<R(Params..., ...)> : std::true_type
{
    using Type                     = R;
    using ParamsT                  = Typelist<Params...>;
    static constexpr bool variadic = true;
};

#endif
