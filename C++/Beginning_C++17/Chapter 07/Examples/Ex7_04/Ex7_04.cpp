// Copyright (c) 2018 Ivor Horton and Peter Van Weert. Some rights reserved.
// Licensed under the Freeware License. See the LICENSE file in the project root for more information.
//
// Name: Ex7_04.cpp - Version 1.0.0
// Author: cdrisko
// Date: 05/03/2020-16:47:47
// Description: Searching within strings

#include <iostream>
#include <string>

int main()
{
    std::string sentence {"Manners maketh man"};
    std::string word {"man"};
    std::cout << sentence.find(word) << std::endl;              // Outputs 15
    std::cout << sentence.find("Ma") << std::endl;              // Outputs 0
    std::cout << sentence.find('k')  << std::endl;              // Outputs 10
    std::cout << sentence.find('x')  << std::endl;              // Outputs std::string::npos
}
