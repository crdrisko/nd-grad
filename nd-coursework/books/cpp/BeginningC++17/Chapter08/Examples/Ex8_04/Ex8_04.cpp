// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_04.cpp
// Author: cdrisko
// Date: 08/10/2020-07:57:25
// Description: Modifying the value of a caller variable

#include <iostream>

double changeIt(double* pointer_to_it);                     // Function prototype

int main()
{
    double it {5.0};
    double result {changeIt(&it)};                          // Now we pass the address

    std::cout << "After function execution, it = " << it
              << "\nResult returned is " << result << std::endl;
}

// Function that attempts to modify an argument and return it
double changeIt(double* pit)
{
    *pit += 10.0;                                           // This modifies the original double
    std::cout << "Within function, *pit = " << *pit << std::endl;
    return *pit;
}
