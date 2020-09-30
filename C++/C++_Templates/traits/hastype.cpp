// Copyright (c) 2017 by Addison-Wesley, David Vandevoorde, Nicolai M. Josuttis, and Douglas Gregor. All rights reserved.
// See the LICENSE file in the project root for more information.
//
// Name: hastype.cpp
// Author: crdrisko
// Date: 08/30/2020-18:34:01
// Description: Using our DEFINE_HAS_TYPE macro to test a few cases on different member types

#include <iostream>
#include <vector>

#include "hastype.hpp"

DEFINE_HAS_TYPE(value_type);
DEFINE_HAS_TYPE(char_type);

int main()
{
    std::cout << "int::value_type: "
              << HasTypeT_value_type<int>::value << '\n';
    std::cout << "std::vector<int>::value_type: "
              << HasTypeT_value_type<std::vector<int>>::value << '\n';
    std::cout << "std::iostream::value_type: "
              << HasTypeT_value_type<std::iostream>::value << '\n';
    std::cout << "std::iostream::char_type: "
              << HasTypeT_char_type<std::iostream>::value << '\n';
}
