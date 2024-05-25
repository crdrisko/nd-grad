// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: foreachn.cpp
// Author: crdrisko
// Date: 11/17/2020-06:54:02
// Description: An example of how to use the new algorithm std::for_each_n()

#include <algorithm>   // for std::for_each_n()
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // initialize a vector of 10,000 string values:
    std::vector<std::string> coll;

    for (int i = 0; i < 1000; ++i)
        coll.push_back(std::to_string(i));

    // modify first 5 elements:
    std::for_each_n(coll.begin(), 5, [](auto& elem) { elem = "value" + elem; });

    // print first 10 elements:
    std::for_each_n(coll.begin(), 10, [](const auto& elem) { std::cout << elem << '\n'; });
}
