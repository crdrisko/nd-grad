// Name: Exercise5_01.cpp - Version 1.0.0
// Author: cdrisko
// Date: 04/30/2020-11:50:29
// Description: Outputting the squares of odd integers from 1 to some upper limit

#include <cmath>
#include <limits>
#include <iostream>

int main()
{
    const size_t highestSquarable_size_t = std::sqrt(std::numeric_limits<size_t>::max()) - 1;

    size_t limit {};
    std::cout << "Please enter an upper limit for the odd integers up to "
                  << highestSquarable_size_t << ": ";
        std::cin  >> limit;

    while (limit < 1 || limit > highestSquarable_size_t)
    {
        std::cout << "Sorry please enter a number from 1 to " << highestSquarable_size_t << ": ";
        std::cin  >> limit;
    }

    for (size_t i {1}; i <= limit; i += 2)
        std::cout << i * i << std::endl;
}
