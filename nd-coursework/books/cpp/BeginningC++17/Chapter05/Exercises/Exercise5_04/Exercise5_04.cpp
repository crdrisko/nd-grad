// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise5_04.cpp
// Author: cdrisko
// Date: 04/30/2020-13:50:55
// Description: Reversing a C-style string using a for loop

#include <iostream>

int main()
{
    const std::size_t maxLength {1000};

    char cStyleString[maxLength] {};
    std::cout << "Enter a string of up to 1000 characters: ";
    std::cin.getline(cStyleString, maxLength);

    int count {};
    for (; count < maxLength && cStyleString[count] != '\0'; ++count) {}

    for (int i {count - 1}; i >= 0; --i)
        std::cout << cStyleString[i];

    std::cout << std::endl;
}
