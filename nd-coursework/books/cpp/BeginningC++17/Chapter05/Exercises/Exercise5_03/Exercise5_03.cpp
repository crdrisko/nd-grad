// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise5_03.cpp
// Author: crdrisko
// Date: 04/30/2020-13:37:08
// Description: Count the number of non-whitespace characters entered by a user

#include <iostream>

int main()
{
    std::size_t count {};
    char character {};
    std::cout << "Enter a sequence of characters terminated by '#': " << std::endl;

    do
    {
        std::cin >> character;
        ++count;
    } while (character != '#');

    std::cout << "You entered " << --count << " non-whitespace characters (not including '#')." << std::endl;
}
