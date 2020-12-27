// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: vartmplauto.hpp
// Author: crdrisko
// Date: 10/31/2020-15:24:01
// Description: A header file defining a global variable template array object

#ifndef VARTMPLAUTO_HPP
#define VARTMPLAUTO_HPP

#include <array>

template<typename T, auto N>
std::array<T, N> arr {};

void printArr();

#endif
