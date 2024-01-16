// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise5_06.cpp
// Author: cdrisko
// Date: 04/30/2020-14:36:04
// Description: Printing elements of a vector 10 to a line

#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    std::size_t limit {}, count {}, perline {10};
    std::cout << "Please enter an upper limit for the integers: ";
    std::cin  >> limit;

    std::vector<std::size_t> data;

    for (std::size_t i {}; i < limit; ++i)
    {
        data.push_back(i + 1);

        if (data[i] % 7 && data[i] % 13)
        {
            std::cout << std::setw(5) << data[i];

            if (++count == perline)
            {
                std::cout << std::endl;
                count = 0;
            }
        }
    }

    std::cout << std::endl;
}
