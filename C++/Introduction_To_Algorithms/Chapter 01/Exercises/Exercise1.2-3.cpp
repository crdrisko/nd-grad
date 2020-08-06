// Name: Exercise1.2-3.cpp - Version 1.0.0
// Author: cdrisko
// Date: 08/03/2020-11:39:38
// Description: Comparing running times of different algorithms

#include <cmath>
#include <iostream>

int main()
{
    int n {1};

    while ( (100 * n * n) > std::pow(2, n) )
    {
        std::cout << n << std::endl;
        ++n;
    }
}
