// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_06.cpp
// Author: crdrisko
// Date: 04/26/2020-15:19:25
// Description: Using a do-while loop to manange input

#include <cctype>   // For tolower() function
#include <iostream>

int main()
{
    char reply {};           // Stores response to prompt for input
    int count {};            // Counts the number of input values
    double temperature {};   // Stores an input value
    double total {};         // Stores the sum of all input values
    do
    {
        std::cout << "Enter a temperature reading: ";   // Prompt for input
        std::cin >> temperature;                        // Read input value

        total += temperature;   // Accumulate total of values
        ++count;                // Increment count

        std::cout << "Do you want to enter another? (y/n): ";
        std::cin >> reply;   // Get response
    } while (std::tolower(reply) == 'y');

    std::cout << "The average temperature is " << total / count << std::endl;
}
