// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex7_08.cpp
// Author: cdrisko
// Date: 05/03/2020-18:06:09
// Description: Formatting using string streams

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::vector<double> values;

    std::cout << "How many numbers do you want to enter? ";
    std::size_t num {};
    std::cin >> num;
    for (std::size_t i {}; i < num; ++i)             // Stream in all 'num' user inputs
    {
        double d {};
        std::cin >> d;
        values.push_back(d);
    }

    std::stringstream ss;                       // Create a new string stream
    for (std::size_t i {}; i < num; ++i)             // Use it to compose the requested string
    {
        ss << std::setprecision(4) << std::setw(7) << std::right << values[i];
        if ((i + 1) % 5 == 0) ss << std::endl;
    }

    std::string s { ss.str() };                 // Extract the resulting string using the str() function
    std::cout << s << std::endl;
}
