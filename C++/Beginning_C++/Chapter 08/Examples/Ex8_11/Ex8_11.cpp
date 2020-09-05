// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex8_11.cpp - Version 1.0.0
// Author: crdrisko
// Date: 08/14/2020-08:11:07
// Description: Using multiple default parameter values

#include <iomanip>
#include <iostream>
#include <string_view>

// The function prototype including defaults for parameters
void show_data(const int data[], std::size_t count = 1, std::string_view title = "Data Values",
    std::size_t width = 10, std::size_t perline = 5);

int main()
{
    int samples[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int dataItem {-99};
    show_data(&dataItem);

    dataItem = 13;
    show_data(&dataItem, 1, "Unlucky for some!");

    show_data(samples, std::size(samples));
    show_data(samples, std::size(samples), "Samples");
    show_data(samples, std::size(samples), "Samples", 6);
    show_data(samples, std::size(samples), "Samples", 8, 4);
}

void show_data(const int data[], std::size_t count, std::string_view title,
    std::size_t width, std::size_t perline)
{
    std::cout << title << std::endl;                        // Display the title

    // Output the data values
    for (std::size_t i {}; i < count; ++i)
    {
        std::cout << std::setw(width) << data[i];           // Display a data item
        if ( (i + 1) % perline == 0 )                       // Newline after perLine values
            std::cout << '\n';
    }
    std::cout << std::endl;
}
