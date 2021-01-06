// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_05.cpp
// Author: cdrisko
// Date: 04/26/2020-09:46:51
// Description: Additional messages printed at the end of Ex4_06

#include <iostream>

int main()
{
    int mice {};                    // Count of all mice
    int brown {};                   // Count of brown mice
    int white {};                   // Count of white mice

    std::cout << "How many brown mice do you have? ";
    std::cin  >> brown;
    std::cout << "How many white mice do you have? ";
    std::cin  >> white;

    mice = brown + white;

    std::cout << "You have " << mice
              << (mice == 1 ? " mouse" : " mice")
              << " in total." << std::endl;

    if (mice == 1)
    {
        std::cout << "It is a " << (brown ? "brown" : "white") << " mouse." << std::endl;
    }
    else if (mice > 1)
    {
        std::cout << "Of these mice, " << brown
                  << (brown == 1 ? " is a brown mouse." : " are brown mice.") << std::endl;
    }
}
