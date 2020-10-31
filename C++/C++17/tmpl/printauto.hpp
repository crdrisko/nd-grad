// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: printauto.hpp
// Author: crdrisko
// Date: 10/31/2020-15:18:25
// Description: Using auto as a template parameter to separate values when printing with either a string or a character

#ifndef PRINTAUTO_HPP
#define PRINTAUTO_HPP

#include <iostream>

template<auto Sep = ' ', typename First, typename... Args>
void print(const First& first, const Args&... args)
{
    std::cout << first;
    auto outWithSep = [](const auto& arg) { std::cout << Sep << arg; };
    (..., outWithSep(args));
    std::cout << '\n';
}

#endif
