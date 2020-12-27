// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: variant.cpp
// Author: crdrisko
// Date: 12/12/2020-06:26:13
// Description: An example usage of the Variant<> class template

#include "variant.hpp"

#include <iostream>
#include <string>

int main()
{
    Variant<int, double, std::string> field(17);

    if (field.is<int>())
        std::cout << "Field stores the integer " << field.get<int>() << '\n';

    field = 42;                                             // assign value of same type
    field = "hello";                                        // assign value of different type

    std::cout << "Field now stores the string '" << field.get<std::string>() << "'\n";
}
