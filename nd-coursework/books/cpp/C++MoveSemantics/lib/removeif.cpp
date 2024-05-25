// Copyright (c) 2020 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: removeif.cpp
// Author: crdrisko
// Date: 08/18/2021-08:03:52
// Description: Using std::remove_if to remove some elements of a vector of our email class

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "email.hpp"

int main()
{
    std::vector<Email> coll {"tom@domain.de", "jill@company.com", "sara@domain.de", "hana@company.com"};

    // remove all email addresses ending with ".de":
    auto newEnd = std::remove_if(coll.begin(),
        coll.end(),
        [](const Email& e)
        {
            auto&& val = e.getValue();
            return val.size() > 2 && val.substr(val.size() - 3) == ".de";
        });

    // print elements up to the new end:
    std::cout << "remaining elements:\n";
    for (auto pos = coll.begin(); pos != newEnd; ++pos)
        std::cout << "  '" << *pos << "'\n";

    // print all elements in the container:
    std::cout << "all elements:\n";
    for (const auto& elem : coll)
        std::cout << "  '" << elem << "'\n";
}
