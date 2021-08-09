// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: intstring.cpp
// Author: crdrisko
// Date: 08/08/2021-07:23:08
// Description: Breaking invariants due to moved consistent value members with our IntString class

#include "intstring.hpp"

#include <iostream>

int main()
{
    IntString is1 {42};
    IntString is2;

    std::cout << "is1 and is2 before move:\n";
    is1.dump();
    is2.dump();

    is2 = std::move(is1);

    std::cout << "is1 and is2 after move:\n";
    is1.dump();
    is2.dump();
}
