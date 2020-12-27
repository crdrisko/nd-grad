// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: invoke.cpp
// Author: crdrisko
// Date: 10/30/2020-07:53:35
// Description: Using our generic function to call member functions of std::vector and print the resulting elements

#include "invoke.hpp"

#include <iostream>
#include <vector>

void print(const std::vector<int>& coll)
{
    std::cout << "elems: ";

    for (const auto& elem : coll)
        std::cout << elem << ' ';

    std::cout << '\n';
}

int main()
{
    std::vector<int> vals {0, 8, 15, 42, 13, -1, 0};

    call([&vals] { std::cout << "size: " << vals.size() << '\n'; });
    call(print, vals);

    call(&decltype(vals)::pop_back, vals);
    call(print, vals);

    call(&decltype(vals)::clear, vals);
    call(print, vals);
}
