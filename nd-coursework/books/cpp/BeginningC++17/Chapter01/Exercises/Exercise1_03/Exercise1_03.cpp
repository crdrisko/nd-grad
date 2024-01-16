// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise1_03.cpp
// Author: cdrisko
// Date: 04/15/2020-08:41:12
// Description: Fixing issues with the supplied problem code

/* Problem Code:
include <iostream>                          <- Missing the hash symbol (#) before include

Int main()                                  <- Int is capitalized, C++ is case-sensitive
{
    std:cout << "Hello World" << std:endl   <- Scope resolution operator has two colons (::), missing semi-colon at the end
)                                           <- Need a curly bracket (}) to close the function block, not a parenthese
*/

#include <iostream>

int main()
{
    std::cout << "Hello World" << std::endl;
}
