// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: literals.hpp
// Author: crdrisko
// Date: 12/05/2020-08:23:52
// Description: Parsing a char array as an integer at compile time

#ifndef LITERALS_HPP
#define LITERALS_HPP

#include <cassert>
#include <cstddef>

#include "ctvalue.hpp"

// convert single char to corresponding int value at compile time:
constexpr int toInt(char c)
{
    // hexadecimal letters:
    if (c >= 'A' && c <= 'F')
        return static_cast<int>(c) - static_cast<int>('A') + 10;

    if (c >= 'a' && c <= 'f')
        return static_cast<int>(c) - static_cast<int>('a') + 10;

    // other (disable '.' for floating-point literals):
    assert(c >= '0' && c <= '9');
    return static_cast<int>(c) - static_cast<int>('0');
}

// parse array of chars to corresponding int value at compile time:
template<std::size_t N>
constexpr int parseInt(char const (&arr)[N])
{
    int base   = 10;   // to handle base (default: decimal)
    int offset = 0;    // to skip prefixes like 0x

    if (N > 2 && arr[0] == '0')
    {
        switch (arr[1])
        {
        case 'x':
        case 'X':   // prefix 0x or 0X, so hexadecimal
            base   = 16;
            offset = 2;
            break;
        case 'b':
        case 'B':   // prefix 0b or 0B, so binary
            base   = 2;
            offset = 2;
            break;
        default:   // prefix 0, so octal
            base   = 8;
            offset = 1;
            break;
        }
    }

    // iterate over all digits and compute resulting value:
    int value      = 0;
    int multiplier = 1;

    for (std::size_t i = 0; i < N - offset; ++i)
    {
        if (arr[N - 1 - i] != '\'')   // ignore separating single quotes (e.g. in 1'000)
        {
            value += toInt(arr[N - 1 - i]) * multiplier;
            multiplier *= base;
        }
    }

    return value;
}

// literal operator: parse integral literals with suffix _c as sequence of chars:
template<char... cs>
constexpr auto operator"" _c()
{
    return CTValue<int, parseInt<sizeof...(cs)>({cs...})> {};
}

#endif
