// Copyright (c) 2020 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise5_08.cpp
// Author: cdrisko
// Date: 04/30/2020-15:02:39
// Description: Outputting the first 93 fibonacci numbers

#include <array>
#include <iostream>

int main()
{
    std::array<std::size_t, 93> fibonacciNumbers {};

    for (std::size_t i {}; i < fibonacciNumbers.size(); ++i)
    {
        if (i == 0 || i == 1)
            fibonacciNumbers[i] = 1;
        else
            fibonacciNumbers[i] = fibonacciNumbers[i - 2] + fibonacciNumbers[i - 1];

        std::cout << fibonacciNumbers[i] << std::endl;
    }
}
