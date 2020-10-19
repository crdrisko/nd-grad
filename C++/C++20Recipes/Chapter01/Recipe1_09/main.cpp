// Copyright (c) 2020 J. Burton Browning and Bruce Sutherland. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: main.cpp
// Author: crdrisko
// Date: 10/12/2020-18:35:50
// Description: Using boost::format

#include <iostream>
#include <string>

#include <boost/format.hpp>

int main()
{
    using namespace std::string_literals;

    std::cout << "Enter your first name: " << std::endl;
    std::string firstName;
    std::cin >> firstName;

    std::cout << "Enter your surname: " << std::endl;
    std::string surname;
    std::cin >> surname;

    auto formattedName = str(boost::format("%1% %2%"s) % firstName % surname);
    std::cout << "You said your name is " << formattedName << std::endl;

    return 0;
}
