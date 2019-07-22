/*************************************************************\ 
|* Name: Ex8_12.cpp                                          *|
|* Author: crdrisko                                          *|
|* Date: 05/21/19-13:21:13                                   *|
|* Description: Program that lists its command line          *|
|*  arguments                                                *|
|*                                                           *|
|*                                                           *|
|* Complile Command: g++ Ex8_12.cpp -o Ex8_12.out -std=c++17 *|
\*************************************************************/

#include <iostream>

int main(int argc, char* argv[])
{
    for (int i {}; i < argc; ++i)
        std::cout << argv[i] << std::endl;
}
