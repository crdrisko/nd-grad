// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variantstorage.hpp
// Author: crdrisko
// Date: 12/12/2020-06:37:14
// Description: A low level representation of the variant storage

#ifndef VARIANTSTORAGE_HPP
#define VARIANTSTORAGE_HPP

#include <new>                                              // for std::launder()

#include "../typelist/largesttype.hpp"

template<typename... Types>
class VariantStorage
{
    using LargestT = LargestType<Typelist<Types...>>;
    alignas(Types...) unsigned char buffer[sizeof(LargestType)];
    unsigned char discriminator = 0;

public:
    unsigned char getDiscriminator() const { return discriminator; }
    void setDiscriminator(unsigned char d) { discriminator = d; }

    void* getRawBuffer() { return buffer; }
    const void* getRawBuffer() const { return buffer; }

    template<typename T>
    T* getBufferAs()
    {
        return std::launder(reinterpret_cast<T*>(buffer));
    }

    template<typename T>
    T const* getBufferAs() const
    {
        return std::launder(reinterpret_cast<T const*>(buffer));
    }
};

#endif
