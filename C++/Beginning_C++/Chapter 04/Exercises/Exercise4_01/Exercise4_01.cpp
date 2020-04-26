// Name: Exercise4_01.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/25/2020-12:55:34
// Description: Determine if two values are equal

#include <iostream>

int main()
{
    int a {}, b {};
    std::cout << "Enter two integers separated by spaces: ";
    std::cin  >> a >> b;

    if (a == b)
        std::cout << "The two integers are the same." << std::endl;
    else
        std::cout << "The two integers are not the same." << std::endl;
}
