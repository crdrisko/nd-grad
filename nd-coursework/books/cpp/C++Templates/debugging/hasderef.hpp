// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hasderef.hpp
// Author: crdrisko
// Date: 10/05/2020-07:14:52
// Description: A trait to determine whether a type is dereferencable

#ifndef HASDEREF_HPP
#define HASDEREF_HPP

#include <type_traits>   // for true_type() and false_type()
#include <utility>       // for declval()

template<typename T>
class HasDereference
{
private:
    template<typename U>
    struct Identity;

    template<typename U>
    static std::true_type test(Identity<decltype(*std::declval<U>())>*);

    template<typename U>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

#endif
