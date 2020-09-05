// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: iscontextualbool.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/04/2020-07:55:07
// Description: A trait to determine whether a type T is contextually convertible bool (implicitly or explicitly)

#ifndef ISCONTEXTUALBOOL_HPP
#define ISCONTEXTUALBOOL_HPP

#include <type_traits>                                      // for true_type and false_type
#include <utility>                                          // for declval()

template<typename T>
class IsContextualBoolT
{
private:
    template<typename T>
    struct Identity;

    template<typename U>
    static std::true_type test(Identity<decltype(std::declval<U>() ? 0 : 1)>*);

    template<typename U>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template<typename T>
constexpr bool IsContextualBool = IsContextualBoolT<T>::value;

#endif
