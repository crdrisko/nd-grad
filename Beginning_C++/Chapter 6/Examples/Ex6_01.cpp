/*************************************************************\ 
|* Name: Ex6_01.cpp                                          *|
|* Author: crdrisko                                          *|
|* Description: The size of pointers                         *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex6_01.cpp -o Ex6_01.out -std=c++17 *|
\*************************************************************/

#include <iostream>

int main()
{
    // Print out the size (in number of bytes) of some data types
    // and the corresponding pointer types:
    std::cout << sizeof(double) << " > " << sizeof(char) << std::endl;
    std::cout << sizeof(double*) << " == " << sizeof(char*) << std::endl;
}