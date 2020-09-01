// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: isreference.hpp - Version 1.0.0
// Author: crdrisko
// Date: 09/01/2020-07:48:14
// Description: Determining if a type is a reference, based on std::is_reference<>

#ifndef ISREFERENCE_HPP
#define ISREFERENCE_HPP

#include "ifthenelse.hpp"
#include "islvaluereference.hpp"
#include "isrvaluereference.hpp"

template<typename T>
class IsReferenceT : public IfThenElseT<IsLValueReferenceT<T>::value,
                                        IsLValueReferenceT<T>,
                                        IsRValueReferenceT<T>
                                       >::Type {};

#endif
