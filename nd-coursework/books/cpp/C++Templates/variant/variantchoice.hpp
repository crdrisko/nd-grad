// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variantchoice.hpp
// Author: crdrisko
// Date: 12/12/2020-06:47:27
// Description: The core operations needed to operate on the buffer when the variant's active value is (or will be) of type T

#ifndef VARIANTCHOICE_HPP
#define VARIANTCHOICE_HPP

#include "../typelist/typelist.hpp"
#include "findindexof.hpp"
#include "variant.hpp"

template<typename T, typename... Types>
class VariantChoice
{
    using Derived = Variant<Types...>;
    Derived& getDerived() { return *static_cast<Derived*>(this); }
    Derived const& getDerived() const { return *static_cast<Derived const*>(this); }

protected:
    // compute the discriminator to be used for this type
    constexpr static unsigned Discriminator = FindIndexOfT<Typelist<Types...>, T>::value + 1;

public:
    VarianceChoice() {}
    VarianceChoice(T const& value);                         // see variantchoiceinit.hpp
    VarianceChoice(T&& value);                              // see variantchoiceinit.hpp
    bool destroy();                                         // see variantchoicedestroy.hpp
    Derived& operator=(T const& value);                     // see variantchoiceassign.hpp
    Derived& operator=(T&& value);                          // see variantchoiceassign.hpp
};

#endif
