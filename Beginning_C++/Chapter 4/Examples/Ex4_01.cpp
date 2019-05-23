/*************************************************************\ 
|* Name: Ex4_01.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: Comparing data values                        *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex4_01.cpp -o Ex4_01.out -std=c++17 *|
\*************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    char first {};                          // Stores the first character
    char second {};                         // Stores the second character

    std::cout << "Enter a character: ";
    std::cin  >> first;

    std::cout << "Enter a second character: ";
    std::cin  >> second;

    std::cout << std::boolalpha;
    std::cout << "The value of the expresion " << first << "<" << second
              << " is: " << (first < second) << std::endl;
    std::cout << "The value of the expresion " << first << "==" << second
              << " is: " << (first == second) << std::endl;
}