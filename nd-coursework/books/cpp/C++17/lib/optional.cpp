// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: optional.cpp
// Author: crdrisko
// Date: 11/01/2020-10:07:14
// Description: Returning a std::optional type when attempting to convert a string

#include <iostream>
#include <optional>
#include <string>

// convert string to int if possible:
std::optional<int> asInt(const std::string& s)
{
    try
    {
        return std::stoi(s);
    }
    catch (...)
    {
        return std::nullopt;
    }
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
