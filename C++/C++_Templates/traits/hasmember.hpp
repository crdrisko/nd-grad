// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hasmember.hpp
// Author: crdrisko
// Date: 08/31/2020-07:53:22
// Description: A macro we can use to create traits that detect arbitrary nontype member

#ifndef HASMEMBER_HPP
#define HASMEMBER_HPP

#include <type_traits>                                      // for true_type, false_type, and void_t

#define DEFINE_HAS_MEMBER(Member)                                       \
    template<typename, typename = std::void_t<>>                        \
    struct HasMemberT_##Member                                          \
        : std::false_type {};                                           \
    template<typename T>                                                \
    struct HasMemberT_##Member<T, std::void_t<decltype(&T::Member)>>    \
        : std::true_type {}     // ; intentionally skipped

#endif
