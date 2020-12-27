// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variadictransform.hpp
// Author: crdrisko
// Date: 10/02/2020-08:30:22
// Description: Using pack expansions to simplify and improve the performance of the transform algorithm

#ifndef VARIADICTRANSFORM_HPP
#define VARIADICTRANSFORM_HPP

#include "transform.hpp"
#include "typelist.hpp"

template<typename... Elements, template<typename T> class MetaFun>
class TransformT<Typelist<Elements...>, MetaFun, false>
{
public:
    using Type = Typelist<typename MetaFun<Elements>::Type...>;
};

#endif
