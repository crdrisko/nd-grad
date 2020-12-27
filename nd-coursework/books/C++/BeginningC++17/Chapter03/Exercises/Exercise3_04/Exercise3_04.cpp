// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise3_04.cpp
// Author: cdrisko
// Date: 04/23/2020-14:55:48
// Description: Combine 4 characters into a word and output the word in hexadecimal notation

#include <iomanip>
#include <iostream>

int main()
{
    unsigned int combined {};

    unsigned char a {}, b {}, c {}, d {};
    std::cout << "Enter four characters separated by spaces: ";
    std::cin  >> a >> b >> c >> d;

    combined |= a;
    combined <<= 8;

    combined |= b;
    combined <<= 8;

    combined |= c;
    combined <<= 8;

    combined |= d;

    std::cout << "The word containing 4 packed characters is " << std::right
              << std::hex << std::showbase << std::internal << std::setfill('0') << combined << std::endl;

    std::cout << std::setfill(' ');

    unsigned int mask {0x000000FF};

    std::cout << std::setw(4) << static_cast<unsigned char>((combined >> 0) & mask)
              << std::setw(4) << static_cast<unsigned char>((combined >> 8) & mask)
              << std::setw(4) << static_cast<unsigned char>((combined >> 16) & mask)
              << std::setw(4) << static_cast<unsigned char>((combined >> 24) & mask)
              << std::endl;
}
