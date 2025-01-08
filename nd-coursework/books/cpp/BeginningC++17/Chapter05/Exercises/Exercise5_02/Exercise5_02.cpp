// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise5_02.cpp
// Author: crdrisko
// Date: 04/30/2020-13:15:00
// Description: Calculate the sum and average of user-entered numbers

#include <cctype>
#include <iomanip>
#include <iostream>

int main()
{
    std::size_t input {}, total {}, count {};
    char userResponse {'y'};

    while (userResponse == 'y')
    {
        std::cout << "Please enter an integer number: ";
        std::cin >> input;

        total += input;
        ++count;

        std::cout << "Would you like to enter another number? (y/n) ";
        std::cin >> userResponse;

        if (std::tolower(userResponse) != 'y' && std::tolower(userResponse) != 'n')
        {
            std::cout << "Sorry only 'y' and 'n' were valid responses." << std::endl;
            return 1;
        }
    }

    std::cout << "The total sum of the numbers entered is " << total << " and the average is " << std::fixed
              << std::setprecision(2) << static_cast<float>(total) / count << std::endl;
}
