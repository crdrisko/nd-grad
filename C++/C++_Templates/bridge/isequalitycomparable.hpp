// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isequalitycomparable.hpp - Version 1.0.0
// Author: cdrisko
// Date: 07/27/2020-16:17:39
// Description: Querying whether the operator== is available before calling it

#ifndef ISEQUALITYCOMPARABLE_HPP
#define ISEQUALITYCOMPARABLE_HPP

#include <type_traits>                                      // for true_type and false_type
#include <utility>                                          // for declval()

template<typename T>
class IsEqualityComparable
{
private:
    // test convertibility of == and ! == to bool:
    static void* conv(bool);                                // to check convertibility to bool
    template<typename U>
    static std::true_type test(decltype(conv(std::declval<U const&>() ==
                                             std::declval<U const&>())),
                               decltype(conv(!(std::declval<U const&>() ==
                                               std::declval<U const&>())))
                              );

    // fallback:
    template<typename U>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(nullptr, nullptr))::value;
};

#endif
