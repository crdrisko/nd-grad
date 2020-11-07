// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: addconst.hpp
// Author: crdrisko
// Date: 09/30/2020-07:20:26
// Description: A metafunction for turning a type into its const-qualified variant

#ifndef ADDCONST_HPP
#define ADDCONST_HPP

template<typename T>
struct AddConstT
{
    using Type = T const;
};

template<typename T>
using AddConst = typename AddConstT<T>::Type;

#endif
