/***********************************************************************\ 
|* Name: Exercise5_8.cpp                                               *|
|* Author: crdrisko                                                    *|
|* Description: Prints the first 93 numbers in the Fibonacci sequence. *|
|*                                                                     *|
|*                                                                     *|
|* Complile Command: g++ Exercise5_8.cpp -o Exercise5_8.out -std=c++17 *|
\***********************************************************************/

#include <iostream>
#include <array>


int main()
{
    std::array<unsigned long long, 95> numbers {1UL};
    for (size_t i {2}; i < 95; ++i)
    {
        numbers[i] = numbers[i-1] + numbers[i-2];
        std::cout << i-1 << ") " << numbers[i] << std::endl;
    }
}