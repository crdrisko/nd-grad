// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: factory.hpp
// Author: crdrisko
// Date: 09/29/2020-18:14:34
// Description: The definition of a factory function that always works, even when copying or moving isn't allowed

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <utility>

template<typename T, typename... Args>
T create(Args&&... args)
{
    // ...
    return T{std::forward<Args>(args)...};
}

#endif
