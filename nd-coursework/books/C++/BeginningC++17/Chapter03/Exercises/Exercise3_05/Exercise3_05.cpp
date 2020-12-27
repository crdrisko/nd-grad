// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise3_05.cpp
// Author: cdrisko
// Date: 04/23/2020-14:55:52
// Description: Getting the RGB values of colors using enumerations

#include <iomanip>
#include <iostream>

int main()
{
    const unsigned int R {0x00FF0000};
    const unsigned int G {0x0000FF00};
    const unsigned int B {0x000000FF};

    enum class Color : unsigned int
    {
        Red    = R,
        Green  = G,
        Blue   = B,
        Yellow = R | G,
        Purple = R | B,
        Black  = R & G & B,
        White  = R | G | B
    };

    Color yellow {Color::Yellow};
    Color purple {Color::Purple};
    Color green {Color::Green};

    std::cout << "\nThe color yellow consists of: "
              << "\nRed:   " << ((static_cast<unsigned int>(yellow) & R) >> 16)
              << "\nGreen: " << ((static_cast<unsigned int>(yellow) & G) >> 8)
              << "\nBlue:  " << ((static_cast<unsigned int>(yellow) & B) >> 0)
              << std::endl;

    std::cout << "\nThe color purple consists of: "
              << "\nRed:   " << ((static_cast<unsigned int>(purple) & R) >> 16)
              << "\nGreen: " << ((static_cast<unsigned int>(purple) & G) >> 8)
              << "\nBlue:  " << ((static_cast<unsigned int>(purple) & B) >> 0)
              << std::endl;

    std::cout << "\nThe color green consists of: "
              << "\nRed:   " << ((static_cast<unsigned int>(green) & R) >> 16)
              << "\nGreen: " << ((static_cast<unsigned int>(green) & G) >> 8)
              << "\nBlue:  " << ((static_cast<unsigned int>(green) & B) >> 0)
              << std::endl;
}
