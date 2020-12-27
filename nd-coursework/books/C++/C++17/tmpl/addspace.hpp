// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: addspace.hpp
// Author: crdrisko
// Date: 10/29/2020-13:48:09
// Description: Printing a list of arguments separated by a space using fold expressions

#ifndef ADDSPACE_HPP
#define ADDSPACE_HPP

#include <iostream>

template<typename T>
const T& spaceBefore(const T& arg)
{
    std::cout << ' ';
    return arg;
}

template<typename First, typename... Args>
void print(const First& firstarg, const Args&... args)
{
    std::cout << firstarg;
    (std::cout << ... << spaceBefore(args)) << '\n';
}

#endif
