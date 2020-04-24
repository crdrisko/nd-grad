// Name: Exercise3_03.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/23/2020-14:32:21
// Description: Predict the output of the following code

#include <iostream>

int main()
{
    auto k {430u};
    auto j {(k >> 4) & ~(~0u << 3)};
    std::cout << j << std::endl;
}
