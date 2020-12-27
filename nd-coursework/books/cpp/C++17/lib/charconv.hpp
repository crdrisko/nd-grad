// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: charconv.hpp
// Author: crdrisko
// Date: 11/01/2020-11:32:26
// Description: Using std::to_chars and std::from_chars to convert a double to a string and back to a double

#ifndef CHARCONV_HPP
#define CHARCONV_HPP

#include <cassert>
#include <charconv>
#include <iostream>
#include <system_error>

void d2str2d(double value1)
{
    std::cout << "in:  " << value1 << '\n';

    // convert to character sequence:
    char str[1000];
    std::to_chars_result res1 = std::to_chars(str, str + 999, value1);

    *res1.ptr = '\0';                                       // add trailing null character

    std::cout << "str: " << str << '\n';
    assert(res1.ec == std::errc {});

    // read back from character sequence:
    double value2;
    std::from_chars_result res2 = std::from_chars(str, str + 999, value2);

    std::cout << "out: " << value2 << '\n';
    assert(res2.ec == std::errc {});

    assert(value1 == value2);                               // should never fail
}

#endif
