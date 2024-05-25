// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isconvertible.hpp
// Author: crdrisko
// Date: 09/04/2020-07:36:06
// Description: A trait to determine if a type is convertible to another

#ifndef ISCONVERTIBLE_HPP
#define ISCONVERTIBLE_HPP

#include <utility>

template<typename FROM, typename TO>
struct IsConvertibleT
{
private:
    // to check whether we can call this helper func for a FROM object:
    static void func(TO);

    // test() trying to call the helper func():
    template<typename F, typename T, typename = decltype(func(std::declval<F>()))>
    static char test(void*);

    // test() fallback:
    template<typename, typename>
    static long test(...);

public:
    static constexpr bool value = sizeof(test<FROM, TO>(nullptr)) == 1;
};

template<typename FROM, typename TO>
constexpr bool IsConvertible = IsConvertibleT<FROM, TO>::value;

#endif
