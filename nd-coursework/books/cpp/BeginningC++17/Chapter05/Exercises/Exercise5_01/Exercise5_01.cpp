// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise5_01.cpp
// Author: cdrisko
// Date: 04/30/2020-11:50:29
// Description: Outputting the squares of odd integers from 1 to some upper limit

#include <cmath>
#include <iostream>
#include <limits>

int main()
{
    const std::size_t highestSquarable_size_t = std::sqrt(std::numeric_limits<std::size_t>::max()) - 1;

    std::size_t limit {};
    std::cout << "Please enter an upper limit for the odd integers up to " << highestSquarable_size_t << ": ";
    std::cin >> limit;

    while (limit < 1 || limit > highestSquarable_size_t)
    {
        std::cout << "Sorry please enter a number from 1 to " << highestSquarable_size_t << ": ";
        std::cin >> limit;
    }

    for (std::size_t i {1}; i <= limit; i += 2)
        std::cout << i * i << std::endl;
}
