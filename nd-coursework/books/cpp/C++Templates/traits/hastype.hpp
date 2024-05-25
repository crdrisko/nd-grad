// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hastype.hpp
// Author: crdrisko
// Date: 08/30/2020-18:20:59
// Description: A macro we can use to create traits that detect arbitrary member types

#ifndef HASTYPE_HPP
#define HASTYPE_HPP

#include <type_traits>   // for true_type, false_type, and void_t

#define DEFINE_HAS_TYPE(MemType)                                                                                            \
    template<typename, typename = std::void_t<>>                                                                            \
    struct HasTypeT_##MemType : std::false_type                                                                             \
    {                                                                                                                       \
    };                                                                                                                      \
    template<typename T>                                                                                                    \
    struct HasTypeT_##MemType<T, std::void_t<typename T::MemType>> : std::true_type                                         \
    {                                                                                                                       \
    }   // ; intentionally skipped

#endif
