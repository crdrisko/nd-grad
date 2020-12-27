// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: asint.cpp
// Author: crdrisko
// Date: 11/07/2020-17:25:35
// Description: A function for converting a string to an integer if it's possible

#include <charconv>                                         // for from_chars()
#include <iostream>
#include <optional>
#include <string_view>

// convert string to int if possible:
std::optional<int> asInt(std::string_view sv)
{
    int val;

    // read character sequence into the int:
    auto [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), val);

    // if we have an error code, return no value:
    if (ec != std::errc {})
        return std::nullopt;

    return val;
}

int main()
{
    for (auto s : {"42", "  077", "hello", "0x33"})
    {
        // try to convert s to int and print the result if possible:
        std::optional<int> oi = asInt(s);

        if (oi)
            std::cout << "convert '" << s << "' to int: " << *oi << "\n";
        else
            std::cout << "can't convert '" << s << "' to int\n";
    }
}
