// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isenum.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-09:37:21
// Description: Determining if a type is a enumeration, based on std::is_enum<>

#ifndef ISENUM_HPP
#define ISENUM_HPP

#include "isarray.hpp"
#include "isclass.hpp"
#include "isfunction.hpp"
#include "isfunda.hpp"
#include "ispointer.hpp"
#include "ispointertomember.hpp"
#include "isreference.hpp"

template<typename T>
struct IsEnumT
{
    static constexpr bool value = !IsArrayT<T>::value &&
                                  !IsClassT<T>::value &&
                                  !IsFunctionT<T>::value &&
                                  !IsFundaT<T>::value &&
                                  !IsPointerT<T>::value &&
                                  !IsPointerToMemberT::value &&
                                  !IsReference<T>::value;
};

#endif
