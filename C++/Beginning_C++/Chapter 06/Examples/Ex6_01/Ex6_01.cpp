// Name: Ex6_01.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/30/2020-21:41:31
// Description: The size of pointers

#include <iostream>

int main()
{
    // Print out the size (in number of bytes) of some data types
    // and the corresponding pointer types:
    std::cout << sizeof(double) << " > " << sizeof(char) << std::endl;
    std::cout << sizeof(double*) << " == " << sizeof(char*) << std::endl;
}
