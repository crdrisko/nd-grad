// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex5_07.cpp
// Author: crdrisko
// Date: 04/26/2020-15:35:23
// Description: Generating multiplication tables using nested loops

#include <cctype>
#include <iomanip>
#include <iostream>

int main()
{
    std::size_t table {};               // Table size
    const std::size_t table_min {2};    // Minimum table size - at least up to the 2-times
    const std::size_t table_max {12};   // Maximum table size
    char reply {};                      // Response to prompt

    do
    {
        std::cout << "What size table would you like (" << table_min << " to " << table_max << ")? ";
        std::cin >> table;   // Get the table size
        std::cout << std::endl;

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
        {                                                    // Iterate over rows
            std::cout << " " << std::setw(3) << i << " |";   // Start the row

            // Output the values in a row
            for (std::size_t j {1}; j <= table; ++j)
            {
                std::cout << " " << std::setw(3) << i * j << " |";   // For each col.
            }
            std::cout << std::endl;   // End the row
        }

        // Check if another table is required
        std::cout << "\nDo you want another table (y or n)? ";
        std::cin >> reply;

    } while (std::tolower(reply) == 'y');
}
