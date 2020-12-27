// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: overload.hpp
// Author: crdrisko
// Date: 10/31/2020-15:46:36
// Description: Creating a structure that can overload lambda functions

#ifndef OVERLOAD_HPP
#define OVERLOAD_HPP

// "inherit" all function call operators of passed base types:
template<typename... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};

// base types are deduced from passed arguments
template<typename... Ts>
overload(Ts...) -> overload<Ts...>;

#endif
