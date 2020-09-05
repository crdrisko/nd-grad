// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_07.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/13/2020-07:45:12
// Description: Modifying the value of a caller variable - references vs. pointers

#include <iostream>

void change_it_by_pointer(double* pit);                     // Pass pointer (by value)
void change_it_by_reference(double& rit);                   // Pass by reference

int main()
{
    double it {5.0};

    change_it_by_pointer(&it);                              // Now we pass the address
    std::cout << "After first function execution, it = " << it << std::endl;

    change_it_by_reference(it);                             // Now we pass a reference, not the value!
    std::cout << "After second function execution, it = " << it << std::endl;
}

void change_it_by_pointer(double* pit)
{
    *pit += 10.0;                                           // This modifies the original double
}

void change_it_by_reference(double& rit)
{
    rit += 10.0;                                            // This modifies the original value as well!
}
