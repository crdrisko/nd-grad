// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: lessresult.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/04/2020-07:55:07
// Description: A trait that checks for the < operator and computes its result

#ifndef LESSRESULT_HPP
#define LESSRESULT_HPP

#include <type_traits>                                      // for true_type and false_type
#include <utility>                                          // for declval()

template<typename T1, typename T2>
class HasLess
{
    template<typename T>
    struct Identity;

    template<typename U1, typename U2>
    static std::true_type test(Identity<decltype(std::declval<U1>() < std::declval<U2>())>*);

    template<typename U1, typename U2>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T1, T2>(nullptr))::value;
};


template<typename T1, typename T2, bool HasLess>
class LessResultImpl
{
public:
    using Type = decltype(std::declval<T1>() < std::declval<T2>());
};

template<typename T1, typename T2>
class LessResultImpl<T1, T2, false> {};


template<typename T1, typename T2>
class LessResultT : public LessResultImpl<T1, T2, HasLess<T1, T2>::value> {};

template<typename T1, typename T2>
using LessResult = typename LessResultT<T1, T2>::Type;

#endif
