// Copyright (c) 2019-2021 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise7_07.cpp
// Author: cdrisko
// Date: 08/06/2020-07:26:52
// Description: Using stringstreams to parse strings

#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string numbers;
    std::cout << "Enter a sequence of integers separated by spaces and terminated by #:\n";
    std::getline(std::cin, numbers, '#');

    long sum {};
    std::stringstream numberStream {numbers};

    while (numberStream)
    {
        long i {};
        numberStream >> i;
        sum += i;
    }

    std::cout << "The sum of the numbers you entered is " << sum << std::endl;
}
