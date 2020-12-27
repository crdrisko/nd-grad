// Copyright (c) 2017 by Nicolai Josuttis. All rights reserved.
// Licensed under the CCA-4.0 International License. See the LICENSE file in the project root for more information.
//
// Name: evalexcept.cpp
// Author: crdrisko
// Date: 09/29/2020-18:28:13
// Description: Demonstrating backward incompatibilities with regards to the order of evaluation

#include <iostream>
#include <vector>

void print10elems(const std::vector<int>& v)
{
    for (int i = 0; i < 10; ++i)
        std::cout << "value: " << v.at(i) << '\n';
}

int main()
{
    try
    {
        std::vector<int> vec {7, 14, 21, 28};
        print10elems(vec);
    }
    catch(const std::exception& e)                          // handle standard exception
    {
        std::cerr << "EXCEPTION: " << e.what() << '\n';
    }
    catch(...)                                              // handle any other exception
    {
        std::cerr << "EXCEPTION of unknown type\n";
    }
}
