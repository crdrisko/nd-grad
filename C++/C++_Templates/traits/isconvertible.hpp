// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isconvertible.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/30/2020-13:07:21
// Description: A trait to determine if a type is convertible to another, based on std::is_convertible<>

#ifndef ISCONVERTIBLE_HPP
#define ISCONVERTIBLE_HPP

#include <type_traits>
#include <utility>

template<typename FROM, typename TO>
struct IsConvertibleHelper
{
private:
    static void aux(TO);

    // test() trying to call the helper aux(TO) for a FROM passed as F:
    template<typename F, typename,
             typename = decltype(aux(std::declval<F>()))>
    static std::true_type test(void*);

    // test() fallback:
    template<typename, typename>
    static std::false_type test(...);

public:
    using Type = decltype(test<FROM>(nullptr));
};

template<typename FROM, typename TO>
struct IsConvertibleT : IsConvertibleHelper<FROM, TO>::Type {};

template<typename FROM, typename TO>
using IsConvertible = typename IsConvertibleT<FROM, TO>::Type;

template<typename FROM, typename TO>
constexpr bool IsConvertible = IsConvertibleT<FROM, TO>::value;


#endif
