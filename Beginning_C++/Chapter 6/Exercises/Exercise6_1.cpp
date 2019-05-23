/***********************************************************************\ 
|* Name: Exercise6_1.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Prints the first 50 odd numbers, 10 to a row, forwards *|
|*   and backwards.                                                    *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise6_1.cpp -o Exercise6_1.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <iomanip>
#include <array>

int main()
{
    const unsigned int max {50};
    std::array<int, max> odd_array {};
    for (size_t i {}; i < max; ++i)
    {
        odd_array[i] = 2*i + 1;
        std::cout << std::setw(4) << odd_array[i];
        if ((i+1) % 10 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
    for (size_t i {}; i < max; ++i)
    {
        odd_array[i] = 100 - (2*i + 1);
        std::cout << std::setw(4) << odd_array[i];
        if ((i+1) % 10 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}