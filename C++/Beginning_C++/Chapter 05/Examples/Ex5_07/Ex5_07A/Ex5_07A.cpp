// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for license information.
//
// Name: Ex5_07A.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/27/2020-13:55:14
// Description: Generating multiplication tables using an indefinite for loop and break statements

#include <cctype>                                                   // For std::tolower()
#include <iomanip>
#include <iostream>

int main()
{
    std::size_t table {};                                                // Table size
    const std::size_t table_min {2};                                     // Minimum table size - at least up to the 2-times
    const std::size_t table_max {12};                                    // Maximum table size
    const std::size_t max_tries {3};                                     // Maximum number of times user is allowed to try entering a table size
    char reply {};                                                  // Response to prompt

    do
    {
        for (std::size_t count {1}; ; ++count)                           // Indefinite loop
        {
            std::cout << "What size table would you like ("
                      << table_min << " to " << table_max << ")? ";
            std::cin  >> table;                                     // Get the table size

            // Make sure table size is within the limits
            if (table >= table_min && table <= table_max)
            {
                break;                                              // Exit the input loop
            }
            else if (count < max_tries)
            {
                std::cout << "Invalid input - try again.\n";
            }
            else
            {
                std::cout << "Invalid table size entered - yet again! \nSorry, only "
                          << max_tries << " allowed - program terminated." << std::endl;
                return 1;
            }
        }

        // Make sure table is within the limits
        if (table < table_min || table > table_max)
        {
            std::cout << "Invalid table size entered. Program terminated." << std::endl;
            return 1;
        }

        // Create the top line of the table
        std::cout << std::setw(6) << " |";
        for (std::size_t i {1}; i <= table; ++i)
        {
            std::cout << " " << std::setw(3) << i << " |";
        }
        std::cout << std::endl;

        // Create the separator row
        for (std::size_t i {}; i <= table; ++i)
        {
            std::cout << "------";
        }
        std::cout << std::endl;

        for (std::size_t i {1}; i <= table; ++i)
        {   // Iterate over rows
            std::cout << " " << std::setw(3) << i << " |";          // Start the row

            // Output the values in a row
            for (std::size_t j {1}; j <= table; ++j)
            {
                std::cout << " " << std::setw(3) << i * j << " |";  // For each col.
            }
            std::cout << std::endl;                                 // End the row
        }

        // Check if another table is required
        std::cout << "\nDo you want another table (y or n)? ";
        std::cin  >> reply;

    } while (std::tolower(reply) == 'y');
}
