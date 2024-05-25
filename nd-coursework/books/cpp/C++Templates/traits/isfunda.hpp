// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isfunda.hpp
// Author: crdrisko
// Date: 09/01/2020-07:19:49
// Description: A trait to determine if the given type is a fundamental type or not, based on std::is_fundamental

#ifndef ISFUNDA_HPP
#define ISFUNDA_HPP

#include <cstddef>       // for nullptr_t
#include <type_traits>   // for true_type, false_type, and bool_constant<>

// primary template: in general T is not a fundamental type
template<typename T>
struct IsFundaT : std::false_type
{
};

// macro to specialize for fundamental types:
#define MK_FUNDA_TYPE(T)                                                                                                    \
    template<>                                                                                                              \
    struct IsFundaT<T> : std::true_type                                                                                     \
    {                                                                                                                       \
    };

MK_FUNDA_TYPE(void)

MK_FUNDA_TYPE(bool)
MK_FUNDA_TYPE(char)
MK_FUNDA_TYPE(signed char)
MK_FUNDA_TYPE(unsigned char)
MK_FUNDA_TYPE(wchar_t)
MK_FUNDA_TYPE(char16_t)
MK_FUNDA_TYPE(char32_t)

MK_FUNDA_TYPE(signed short)
MK_FUNDA_TYPE(unsigned short)
MK_FUNDA_TYPE(signed int)
MK_FUNDA_TYPE(unsigned int)
MK_FUNDA_TYPE(signed long)
MK_FUNDA_TYPE(unsigned long)
MK_FUNDA_TYPE(signed long long)
MK_FUNDA_TYPE(unsigned long long)

MK_FUNDA_TYPE(float)
MK_FUNDA_TYPE(double)
MK_FUNDA_TYPE(long double)

MK_FUNDA_TYPE(std::nullptr_t)

#undef MK_FUNDA_TYPE

#endif
