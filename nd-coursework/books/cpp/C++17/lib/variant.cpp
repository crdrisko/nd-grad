// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: variant.cpp
// Author: crdrisko
// Date: 11/08/2020-07:05:10
// Description: Demonstrating the core abilities of std::variant<>

#include <iostream>
#include <variant>

int main()
{
    std::variant<int, std::string> var {"hi"};   // initialized with string alternative
    std::cout << var.index() << '\n';            // prints 1
    var = 42;                                    // now holds int alternative
    std::cout << var.index() << '\n';            // prints 0
    // ...

    try
    {
        int i         = std::get<0>(var);             // access by index
        std::string s = std::get<std::string>(var);   // access by type (throws exception here)
        // ...
    }
    catch (const std::bad_variant_access& e)   // in case a wrong type/index is used
    {
        std::cerr << "EXCEPTION: " << e.what() << '\n';
        // ...
    }
}
