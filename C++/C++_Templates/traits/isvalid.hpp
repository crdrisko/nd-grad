// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isvalid.hpp - Version 1.0.0
// Author: crdrisko
// Date: 08/29/2020-10:21:32
// Description: Helper functions for determining whether or not certain function calls are valid

#ifndef ISVALID_HPP
#define ISVALID_HPP

#include <utility>

// helper: checking validity of f(args...) for F f and Args... args:
template<typename F, typename... Args,
         typename = decltype(std::declval<F>()(std::declval<Args&&>()...))>
std::true_type isValidImpl(void*);

// fallback if helper SFINAE'd out:
template<typename F, typename... Args>
std::false_type isValidImpl(...);

// define a lambda that takes a lambda f and returns whether calling f with args is valid:
inline constexpr auto isValid = [](auto f) {
    return [](auto&&... args) {
        return decltype( isValidImpl<decltype(f), decltype(args)&&...>(nullptr) ){};
    };
};

// helper template to represent a type as a value:
template<typename T>
struct TypeT
{
    using Type = T;
};

// helper to wrap a type as a value:
template<typename T>
constexpr auto type = TypeT<T>{};

// helper to unwrap a wrapped type in unevaluated contexts:
template<typename T>
T valueT(TypeT<T>);                                         // no definition needed

#endif
