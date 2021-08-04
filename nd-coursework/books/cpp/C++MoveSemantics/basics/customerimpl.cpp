// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: customerimpl.cpp
// Author: crdrisko
// Date: 08/04/2021-07:34:03
// Description: A small program testing the Customer class

#include "customerimpl.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<Customer> coll;
    for (int i = 0; i < 12; ++i)
        coll.push_back(Customer {"TestCustomer " + std::to_string(i - 5)});

    std::cout << "---- sort():\n";
    std::sort(coll.begin(), coll.end(), [](const Customer& c1, const Customer& c2) { return c1.getName() < c2.getName(); });
}
