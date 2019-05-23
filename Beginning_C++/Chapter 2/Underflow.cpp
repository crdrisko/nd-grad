/*******************************************************************\ 
|* Name: Underflow.cpp                                             *|
|* Author: crdrisko                                                *|
|* Description: Example of how the compiler responds when an       *|
|*  unsigned int becomes negative                                  *|
|*                                                                 *|
|* Complile Command: g++ Underflow.cpp -o Underflow.out -std=c++17 *|
\*******************************************************************/

#include <iostream>
#include <cmath>

int main()
{
    unsigned int x {20u};
    int y {30};
    std::cout << x - y << std::endl;
}