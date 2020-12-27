// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: structbind1.cpp
// Author: crdrisko
// Date: 09/28/2020-08:36:20
// Description: Using structured bindings for objects of type Customer

#include <iostream>
#include <string>
#include <utility>

#include "customer1.hpp"
#include "structbind1.hpp"

int main()
{
    Customer c {"Tim", "Starr", 42};

    auto [f, l, v] = c;

    std::cout << "f/l/v:   " << f << ' ' << l << ' ' << v << '\n';

    // modify structured bindings:
    std::string s {std::move(f)};
    l = "Waters";
    v += 10;
    std::cout << "f/l/v:   " << f << ' ' << l << ' ' << v << '\n';
    std::cout << "c:       " << c.getFirst() << ' '
              << c.getLast() << ' ' << c.getValue() << '\n';
    std::cout << "s:       " << s << '\n';
}
