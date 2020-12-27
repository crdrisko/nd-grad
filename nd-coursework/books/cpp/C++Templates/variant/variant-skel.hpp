// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variant-skel.hpp
// Author: crdrisko
// Date: 12/12/2020-07:03:46
// Description: The skeleton of the Variant<> class template

#ifndef VARIANT_SKEL_HPP
#define VARIANT_SKEL_HPP

#include "variantchoice.hpp"
#include "variantstorage.hpp"

template<typename... Types>
class Variant : private VariantStorage<Types...>, private VariantChoice<Types, Types...>...
{
    template<typename T, typename... OtherTypes>
    friend class VariantChoice;                             // enable CRTP

    // ...
};

#endif
