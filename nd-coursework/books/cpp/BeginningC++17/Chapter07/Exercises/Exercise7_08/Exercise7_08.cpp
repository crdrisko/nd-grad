// Copyright (c) 2019-2024 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise7_08.cpp
// Author: cdrisko
// Date: 08/06/2020-07:55:35
// Description: Parsing strings without using stringstreams

#include <iostream>
#include <string>

int main()
{
    std::string numbers;
    std::cout << "Enter a sequence of integers separated by spaces and terminated by #:\n";

    while (true)
    {
        std::string number;
        std::cin >> number;

        if (number == "#")
            break;

        numbers += number + ' ';
    }

    long sum {};
    std::size_t start {numbers.find_first_not_of(' ')};

    while (start != std::string::npos)
    {
        std::size_t end = numbers.find_first_of(' ', start + 1);
        if (end == std::string::npos)
            end = numbers.length();

        sum += std::stoi(numbers.substr(start, end - start));
        start = numbers.find_first_not_of(' ', end + 1);
    }

    std::cout << "The sum of the numbers you entered is " << sum << std::endl;
}
