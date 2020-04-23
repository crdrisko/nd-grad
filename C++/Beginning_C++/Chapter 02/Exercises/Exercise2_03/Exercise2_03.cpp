// Name: Exercise2_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/23/2020-10:42:30
// Description: Convert a length in inches to feet and inches

#include <iostream>

int main()
{
    const unsigned int inches_per_foot {12};

    unsigned int inches {};
    std::cout << "Enter a length in inches: ";
    std::cin  >> inches;

    std::cout << "In " << inches << " inches there are ";

    unsigned int feet { inches / inches_per_foot };
    inches %= inches_per_foot;

    std::cout << feet << " feet and " << inches << " inch(es)." << std::endl;
}
