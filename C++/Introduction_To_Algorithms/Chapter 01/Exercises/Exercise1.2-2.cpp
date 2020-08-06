// Name: Exercise1.2-2.cpp - Version 1.0.0
// Author: cdrisko
// Date: 08/03/2020-11:39:32
// Description: Comparing insertion sort and merge sort efficiencies at low values of n

#include <cmath>
#include <iostream>

int main()
{
    int n {2};

    while ( n < (8 * std::log2(n)) )
    {
        std::cout << n << std::endl;
        ++n;
    }
}
