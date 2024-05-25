// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: structbind2.cpp
// Author: crdrisko
// Date: 09/28/2020-09:06:50
// Description: Using standard bindings for read access and to modify the members of a Customer

#include "structbind2.hpp"

#include <iostream>
#include <string>
#include <utility>

#include "customer2.hpp"

int main()
{
    Customer c {"Tim", "Starr", 42};

    auto [f, l, v] = c;

    std::cout << "f/l/v:    " << f << ' ' << l << ' ' << v << '\n';

    // modify structured bindings via references:
    auto&& [f2, l2, v2] = c;
    std::string s {std::move(f2)};
    f2 = "Ringo";
    v += 10;
    std::cout << "f2/l2/v2: " << f2 << ' ' << l2 << ' ' << v2 << '\n';
    std::cout << "c:        " << c.firstname() << ' ' << c.lastname() << ' ' << c.value() << '\n';
    std::cout << "s:        " << s << '\n';
}
