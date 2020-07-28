// Name: max1.cpp - Version 1.0.0
// Author: cdrisko
// Date: 07/25/2020-20:36:07
// Description: Using the max() function template

#include <iostream>
#include <string>

#include "max1.hpp"

int main()
{
    int i = 42;
    std::cout << "max(7, i):    " << ::max(7, i) << '\n';

    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1, f2):  " << ::max(f1, f2) << '\n';

    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1, s2):  " << ::max(s1, s2) << '\n';
}
