// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: variantpoly2.cpp
// Author: crdrisko
// Date: 11/11/2020-07:05:14
// Description: Printing values in a polymorphic collection with std::variant<>

#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

int main()
{
    using Var = std::variant<int, double, std::string>;

    std::vector<Var> values {42, 0.19, "hello world", 0.815};

    for (const Var& val : values)
    {
        std::visit(
            [](const auto& v)
            {
                if constexpr (std::is_same_v<decltype(v), const std::string&>)
                    std::cout << '"' << v << "\" ";
                else
                    std::cout << v << ' ';
            },
            val);
    }
}
